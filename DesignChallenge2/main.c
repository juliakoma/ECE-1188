#include <stdint.h>
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
    Clock_Init48MHz();

    UART0_Init();    // UART for Bluetooth
    Motor_Init();    // PWM motor setup
    BumpInt_Init(&Bump_Handler);  // Bump interrupts

    UART0_OutString("BlueToothReady: ");
    
    while (1) {
        char cmd = BlueToth_Handler();

    }
}

int BlueTooth_Handler(char cmd){
    if (UART0_CharAvailable()) {
        char cmd = UART0_InChar();
        UART0_OutString("Received: ");
        UART0_OutChar(cmd);
        UART0_OutChar('\n');

        switch (cmd) {
            case 'GO':
                Motor_Forward(DUTY_LEFT, DUTY_RIGHT);
                UART0_OutString("Moving Forward\n");
                break;
            case 'STOP':
                Motor_Stop();
                UART0_OutString("BUMP\n");
                break;
            default:
                UART0_OutString("Unknown Command\n");
        }
    }
}




