// Motor.c
// Runs on MSP432
// Provide mid-level functions that initialize ports and
// set motor speeds to move the robot. Lab 13 solution
// Daniel Valvano
// July 11, 2019

#include <stdint.h>
#include "msp.h"
#include "../inc/CortexM.h"
#include "../inc/PWM.h"

// *******Lab 13 solution*******

// Motor pins configuration
#define LEFT_DIR   (1 << 4)  // P5.4
#define RIGHT_DIR  (1 << 5)  // P5.5
#define LEFT_EN    (1 << 7)  // P3.7
#define RIGHT_EN   (1 << 6)  // P3.6

// ------------Motor_Init------------
// Initialize GPIO pins for motor control.
void Motor_Init(void){
    P5->SEL0 &= ~(LEFT_DIR | RIGHT_DIR);  // P5.4 and P5.5 as GPIO
    P5->SEL1 &= ~(LEFT_DIR | RIGHT_DIR);
    P5->DIR  |=  (LEFT_DIR | RIGHT_DIR);  // Set as output

    P3->SEL0 &= ~(LEFT_EN | RIGHT_EN);  // P3.6 and P3.7 as GPIO
    P3->SEL1 &= ~(LEFT_EN | RIGHT_EN);
    P3->DIR  |=  (LEFT_EN | RIGHT_EN);  // Set as output
    P3->OUT  |=  (LEFT_EN | RIGHT_EN);  // Enable motor drivers

    // Initialize PWM with 15,000 period and 0 duty cycle
    PWM_Init34(15000, 0, 0);
}




// ------------Motor_Stop------------
// Stop the motors and disable the motor drivers.
void Motor_Stop(void){
    P3->OUT &= ~(LEFT_EN | RIGHT_EN); // Disable motors
    PWM_Duty3(0);
    PWM_Duty4(0);
}

// ------------Motor_Forward------------
// Drive both wheels forward with given duty cycles.
void Motor_Forward(uint16_t leftDuty, uint16_t rightDuty){
    P5->OUT &= ~(LEFT_DIR | RIGHT_DIR);  // Set direction forward
    //P3->OUT |= (LEFT_EN | RIGHT_EN);     // Enable motors
    PWM_Duty3(leftDuty);  // Set left motor speed
    PWM_Duty4(rightDuty); // Set right motor speed
}

// ------------Motor_Right------------
// Turn robot to the right (left wheel forward, right wheel backward).
void Motor_Right(uint16_t leftDuty, uint16_t rightDuty){
    P5->OUT &= ~LEFT_DIR;  // Left forward
    P5->OUT |= RIGHT_DIR;  // Right backward
    P3->OUT |= (LEFT_EN | RIGHT_EN);
    PWM_Duty3(leftDuty);
    PWM_Duty4(rightDuty);
}

// ------------Motor_Left------------
// Turn robot to the left (left wheel backward, right wheel forward).
void Motor_Left(uint16_t leftDuty, uint16_t rightDuty){
    P5->OUT |= LEFT_DIR;   // Left backward
    P5->OUT &= ~RIGHT_DIR; // Right forward
    P3->OUT |= (LEFT_EN | RIGHT_EN);
    PWM_Duty3(leftDuty);
    PWM_Duty4(rightDuty);
}

// ------------Motor_Backward------------
// Drive both wheels backward with given duty cycles.
void Motor_Backward(uint16_t leftDuty, uint16_t rightDuty){
    P5->OUT |= (LEFT_DIR | RIGHT_DIR); // Reverse direction
    P3->OUT |= (LEFT_EN | RIGHT_EN);
    PWM_Duty3(leftDuty);
    PWM_Duty4(rightDuty);
}
