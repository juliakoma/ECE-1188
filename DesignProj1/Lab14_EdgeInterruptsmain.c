//// Lab14_EdgeInterruptsmain.c
//// Runs on MSP432, interrupt version
//// Main test program for interrupt-driven bump sensors controlling the robot.
//
//#include <stdint.h>
//#include "msp.h"
//#include "../inc/Clock.h"
//#include "../inc/CortexM.h"
//#include "../inc/LaunchPad.h"
//#include "../inc/Motor.h"
//#include "../inc/BumpInt.h"
//#include "../inc/TExaS.h"
//#include "../inc/Reflectance.h"
//
//uint8_t CollisionData, CollisionFlag;  // Mailbox for collision events
//
//void HandleCollision(uint8_t bumpSensor){
//    Motor_Stop();   // Stop the robot immediately
//    CollisionData = bumpSensor;
//    CollisionFlag = 1;
//}
//
//int main0(void){
//    DisableInterrupts();
//    Clock_Init48MHz();   // Initialize clock (48MHz)
//    Motor_Init();        // Initialize motors
//    BumpInt_Init(&HandleCollision);  // Initialize bump sensor interrupts
//    Reflectance_Init();  // Initialize reflectance sensors
//    TExaS_Init(LOGICANALYZER_P4_765320);
//    EnableInterrupts();
//
//    // Enable motors explicitly
//    P3->OUT |= (LEFT_EN | RIGHT_EN);
//
//    // Start moving forward
//    Motor_Forward(10000, 10000);  // 67% speed
//
//    while(1){
//        if (CollisionFlag){
//            CollisionFlag = 0;
//            Motor_Stop();
//            Clock_Delay1ms(500);
//        }
//        WaitForInterrupt();
//    }
//}
//
