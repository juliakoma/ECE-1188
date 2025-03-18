#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/UART0.h"
#include "../inc/PWM.h"
#include "../inc/BumpInt.h"
#include "../inc/Reflectance.h"
#include "../inc/Motor.h"
#include <stdint.h>
#include "../inc/CortexM.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"

// FSM States
typedef enum {
    IDLE,
    START,
    FORWARD,
    MILD_LEFT,
    MILD_RIGHT,
    SHARP_LEFT,
    SHARP_RIGHT,
    STOP
} State_t;

State_t currentState = IDLE;
uint8_t CollisionFlag = 0;  // Flag for collision detection

// Function prototypes
void FSM_Update(void);
void Sensor_Init(void);
uint8_t Read_Line_Sensors(void);
void HandleCollision(uint8_t bumpSensor);
void WaitForButtonPress(void);
int32_t Read_Line_Position(void);

// Initialize Sensors
void Sensor_Init(void) {
    Reflectance_Init();
    BumpInt_Init(&HandleCollision);  // Use bump sensor interrupts
}

// Read Line Sensors with an increased integration delay (from 1000us to 1500us)
uint8_t Read_Line_Sensors(void) {
    return Reflectance_Read(1200);
}

// Read Line Position using the integrated sensor value
int32_t Read_Line_Position(void) {
    return Reflectance_Position(Read_Line_Sensors());
}

// Handle Bump Collision
void HandleCollision(uint8_t bumpSensor) {
    Motor_Stop();   // Stop immediately
    CollisionFlag = 1; // Set collision flag
    UART0_OutString("Collision detected! Stopping...\n\r");
}

// Wait for Button Press with a moderate debounce delay
void WaitForButtonPress(void) {
    UART0_OutString("Press SW2 (P1.4) to start...\n\r");
    P1->DIR &= ~0x10;  // Set P1.4 as input
    P1->REN |= 0x10;   // Enable pull-up resistor
    P1->OUT |= 0x10;   // Set as pull-up

    while ((P1->IN & 0x10) != 0);  // Wait for SW2 press
    Clock_Delay1ms(10);            // Debounce delay
    while ((P1->IN & 0x10) == 0);    // Wait for SW2 release
}


// In your FSM_Update:
void FSM_Update(void) {
    static uint32_t startTime = 0;
    int32_t sensorData = Read_Line_Position();

    if (CollisionFlag) {
        CollisionFlag = 0;
        currentState = STOP;
        return;
    }

    switch (currentState) {
        case IDLE:
            WaitForButtonPress();
            currentState = START;
            startTime = 0;
            break;

        case START:
            Motor_Forward(2500, 2500);
            startTime += 80;
            if (startTime >= 1500) {  // After ~1.5 seconds, switch to normal mode
                currentState = FORWARD;
            }
            break;

        case FORWARD:
            sensorData = Read_Line_Position();
            // Use thresholds to decide which correction is needed:
            if (sensorData > 8000) {          // Error is very high: line far left
                currentState = SHARP_LEFT;
            } else if (sensorData > 4800) {     // Moderate error to left
                currentState = MILD_LEFT;
            } else if (sensorData < -8000) {    // Error is very high (negative): line far right
                currentState = SHARP_RIGHT;
            } else if (sensorData < -4800) {    // Moderate error to right
                currentState = MILD_RIGHT;
            } else {
                Motor_Forward(2500, 2500);      // Error small: go straight
            }
            break;

        case MILD_LEFT:
            sensorData = Read_Line_Position();
            // For a mild left turn, slow the left motor moderately relative to the right.
            Motor_Forward(1700, 1000);
            // Return to FORWARD if the error is reduced to near zero,
            // or escalate to SHARP_LEFT if error becomes very large.
            if (sensorData <= 800) {
                currentState = FORWARD;
            } else if (sensorData > 8000) {
                currentState = SHARP_LEFT;
            }
            break;

        case MILD_RIGHT:
            sensorData = Read_Line_Position();
            // For a mild right turn, slow the right motor moderately relative to the left.
            Motor_Forward(1000, 1700);
            if (sensorData >= -800) {
                currentState = FORWARD;
            } else if (sensorData < -8000) {
                currentState = SHARP_RIGHT;
            }
            break;

        case SHARP_LEFT:
            sensorData = Read_Line_Position();
            // For a sharp left turn, use a more aggressive speed differential.
            Motor_Forward(1500, 500);
            // Once the error reduces (here below 6000), go back to FORWARD.
            if (sensorData <= 6000) {
                currentState = FORWARD;
            }
            break;

        case SHARP_RIGHT:
            sensorData = Read_Line_Position();
            // For a sharp right turn, use a more aggressive speed differential.
            Motor_Forward(500, 1500);
            if (sensorData >= -6000) {
                currentState = FORWARD;
            }
            break;

        case STOP:
            UART0_OutString("Robot stopped.\n\r");
            Motor_Stop();
            while (1);
    }
}


// Main Function with a moderate update delay (20ms)
int main(void) {
    Clock_Init48MHz();
    UART0_Init();
    Sensor_Init(); // Bump and Reflectance
    Motor_Init();
    EnableInterrupts();

    while (1) {
        FSM_Update();
        Clock_Delay1ms(80);  // Update FSM every 20ms
    }
}
