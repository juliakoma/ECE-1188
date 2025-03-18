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
            //currentState = FORWARD;
            startTime = 0;
            break;

        case START:
            Motor_Forward(2500, 2500);
            startTime += 80;
            if (startTime >= 1500) {  // After 2 seconds, switch to normal mode
                currentState = FORWARD;
            }
            break;
            //-33400,-23800,-14300,-4800,4800,14300,23800,33400
        case FORWARD:
            if(sensorData > 2000) {
                currentState = MILD_LEFT;
            } else if(sensorData < -2000) {
                currentState = MILD_RIGHT;
            } else {
                Motor_Forward(2500, 2500);
            }
            break;

        case MILD_LEFT:
            sensorData = Read_Line_Position();
            Motor_Left(2500, 2525);
            if(sensorData <= 800) {
                currentState = FORWARD;
            }
            break;

        case MILD_RIGHT:
            sensorData = Read_Line_Position();
            Motor_Right(2525, 2500);
            if(sensorData >= -800) {
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
