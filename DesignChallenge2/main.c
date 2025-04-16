#include <stdint.h>
#include <stdbool.h>

#include "msp.h"
#include "../inc/CortexM.h"
#include "UART0.h"
#include "Motor.h"
#include "BumpInt.h"
#include "../inc/Reflectance.h"

// Movement speed constants
#define DUTY_LEFT 2000
#define DUTY_RIGHT 2000

// Variables
bool goFlag = 0;
bool collisionFlag = 0;
uint32_t startTime = 0;
uint32_t endTime = 0;
uint32_t crashCount = 0;
uint16_t distanceLog[100];
uint8_t distanceIndex = 0;
uint16_t maxSpeed = 0;

// Function prototypes
void HandleCollision(uint8_t bumpSensor);
void Sensor_Init(void);
void BlueTooth_Handler(void);


void main(void) {

    Clock_Init48MHz();
    UART0_Init();    // UART for Bluetooth
    Motor_Init();    // PWM motor setup
    Sensor_Init();   // Bump and Reflectance

    while (1) {
        BlueTooth_Handler();

        // Bluetooth command is go
        if (goFlag == 1) {
            uint8_t reflectance = Reflectance_Read(1200);
            // Reached finish line
            if (reflectance != 0) {
                UART0_OutString("Black line detected! Stopping...\n\r");
                Motor_Stop();
                goFlag = 0;
            } else {
                Motor_Forward(DUTY_LEFT, DUTY_RIGHT);
            }
        }

        // Bluetooth command is stop
        if (goFlag == 0) {
            //Motor_Stop();
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
    crashCount++;
    UART0_OutString("Collision detected! Backing up...\n\r");

    Motor_Stop();                 // Fully stop
    Clock_Delay1ms(500);          // Pause for 0.5 seconds
    Motor_Backward(2000, 2000);   // Back up first
    Clock_Delay1ms(300);          // for 0.3 seconds

    goFlag = 1;                   // Resume forward motion in main loop
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
                goFlag = 0;
                break;
            default:
                UART0_OutString("Unknown Command\n");
        }
    }
}


