#include <stdint.h>
#include <stdbool.h>
#include "msp.h"
#include "../inc/CortexM.h"
#include "UART0.h"
#include "Motor.h"
#include "BumpInt.h"

// Movement speed constants (adjust as needed)
#define DUTY_LEFT 1700
#define DUTY_RIGHT 1700

// Bump sensor event handler
void Bump_Handler(uint8_t bumpData) {
    UART0_OutString("BUMP ");
    UART0_OutUDec(bumpData);
    UART0_OutString("\n");
    Motor_Stop();
}

void main(void) {
    // Variables
    bool goFlag;
    
    Clock_Init48MHz();

    UART0_Init();    // UART for Bluetooth
    Motor_Init();    // PWM motor setup
    BumpInt_Init(&Bump_Handler);  // Bump interrupts

    UART0_OutString("BlueToothReady: ");

    while (1) {
        goFlag = BlueTooth_Handler();
        
        if (goFlag == 1){
            // Logic here
        }
        else (goFlag == 0){
            // Stop Logic here
        }
        
        

    }
}

bool BlueTooth_Handler(char cmd){
    if (UART0_CharAvailable()) {
        char cmd = UART0_InChar();
        bool BlueCmd;
        switch (cmd) {
            case 'G':
                Motor_Forward(DUTY_LEFT, DUTY_RIGHT);
                UART0_OutString("Moving Forward\n");
                BlueCmd = 1;
                break;
            case 'S':
                Motor_Stop();
                UART0_OutString("BUMP\n");
                BlueCmd = 0;
                break;
            default:
                UART0_OutString("Unknown Command\n");
        }

        return BlueCmd;
    }
}




