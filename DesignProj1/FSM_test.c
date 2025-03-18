//#include "msp.h"
//#include "../inc/Clock.h"
//#include "../inc/UART0.h"
//#include "../inc/Motor.h"
//#include "../inc/Reflectance.h"
//
//#include <stddef.h>  // Fix: Define NULL
//
//typedef enum {
//    IDLE,
//    FORWARD,
//    MILD_LEFT,
//    SHARP_LEFT,
//    MILD_RIGHT,
//    SHARP_RIGHT,
//    STOP
//} State_t;
//
//// **External FSM Functions and Variables**
//extern void FSM_Update(void);
//extern State_t currentState;
//extern uint8_t Mock_Left;
//extern uint8_t Mock_Right;
//
//// **Simulate Sensor Input**
//void Simulate_Sensors(void) {
//    UART0_OutString("\n\rEnter Line Sensor Data (L R): ");
//    Mock_Left = UART0_InChar() - '0';
//    UART0_OutChar(' ');
//    Mock_Right = UART0_InChar() - '0';
//    UART0_OutChar('\n');
//
//    // **Debugging Print Statements**
//    UART0_OutString("DEBUG: Mock_Left = ");
//    UART0_OutUDec(Mock_Left);
//    UART0_OutString(", Mock_Right = ");
//    UART0_OutUDec(Mock_Right);
//    UART0_OutString("\n\r");
//}
//
//// **Print FSM State**
//void UART_PrintState(State_t state) {
//    UART0_OutString("Current State: ");
//    switch (state) {
//        case IDLE: UART0_OutString("IDLE\n\r"); break;
//        case FORWARD: UART0_OutString("FORWARD\n\r"); break;
//        case MILD_LEFT: UART0_OutString("MILD_LEFT\n\r"); break;
//        case SHARP_LEFT: UART0_OutString("SHARP_LEFT\n\r"); break;
//        case MILD_RIGHT: UART0_OutString("MILD_RIGHT\n\r"); break;
//        case SHARP_RIGHT: UART0_OutString("SHARP_RIGHT\n\r"); break;
//        case STOP: UART0_OutString("STOP\n\r"); break;
//    }
//}
//
//// **Main Function for Testing**
//int main(void) {
//    Clock_Init48MHz();
//    UART0_Init();
//
//    UART0_OutString("Starting FSM Test...\n\r");
//
//    while (1) {
//        Simulate_Sensors();
//        FSM_Update();
//        UART_PrintState(currentState);
//        Clock_Delay1ms(500);
//    }
//}
