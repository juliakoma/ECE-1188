#include <stdint.h>
#include <stdbool.h>
#include "msp.h"
#include "../inc/CortexM.h"
#include "UART0.h"
#include "Motor.h"
#include "BumpInt.h"
#include "../inc/Reflectance.h"

// Movement speed constants
#define DUTY_LEFT 1700
#define DUTY_RIGHT 1700

// Variables
bool goFlag = 0;
bool collisionFlag = 0;

// Function prototypes
void HandleCollision(uint8_t bumpSensor);
void Sensor_Init(void);
void BlueTooth_Handler(void);

// Bump sensor event handler
void Bump_Handler(uint8_t bumpData) {
    UART0_OutString("BUMP ");
    UART0_OutUDec(bumpData);
    UART0_OutString("\n");
    Motor_Stop();
}


void main(void) {

    Clock_Init48MHz();
    UART0_Init();    // UART for Bluetooth
    Motor_Init();    // PWM motor setup
    Sensor_Init();   // Bump and Reflectance
    //EnableInterrupts();

    while (1) {
        BlueTooth_Handler();

        // Bump Occurred
        if (collisionFlag) {
            collisionFlag = 0;
            goFlag = 0;
            continue;
        }

        // Bluetooth command is go
        if (goFlag == 1) {
            uint8_t reflectance = Reflectance_Read(2000);

            // Reached finish line
            if (reflectance > 0xE7) {
                UART0_OutString("Black line detected! Stopping...\n\r");
                Motor_Stop();
                goFlag = 0;
            } else {
                Motor_Forward(DUTY_LEFT, DUTY_RIGHT);
            }
        }

        // Bluetooth command is stop
        if (goFlag == 0) {
            Motor_Stop();
        }
    }
}


// Initialize Sensors
void Sensor_Init(void) {
    Reflectance_Init();
    BumpInt_Init(&HandleCollision);  // Use bump sensor interrupts
}

// Handle Bump Collision
void HandleCollision(uint8_t bumpSensor) {
    Motor_Stop();   // Stop immediately
    collisionFlag = 1; // Set collision flag
    UART0_OutString("Collision detected! Stopping...\n\r");
}

void BlueTooth_Handler(){
    char cmd;
    if (UART0_CharAvailable()) {
        cmd = UART0_InChar();
        UART0_OutString("Command Received is: ");
        UART0_OutChar(cmd);

        switch (cmd) {
            case 'G':
                UART0_OutString("Moving Forward\n");
                goFlag = 1;
                break;

            case 'S':
                Motor_Stop();
                UART0_OutString("BUMP\n");
                goFlag = 0;
                break;
            default:
                UART0_OutString("Unknown Command\n");
        }
    }
}




