// Lab13_Timersmain.c
// Runs on MSP432
// Student starter code for Timers lab
// Daniel and Jonathan Valvano
// July 11, 2019
// PWM output to motor
// Second Periodic interrupt

/* This example accompanies the book
   "Embedded Systems: Introduction to Robotics,
   Jonathan W. Valvano, ISBN: 9781074544300, copyright (c) 2019
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2019, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/
// Negative logic bump sensors
// P4.7 Bump5, left side of robot
// P4.6 Bump4
// P4.5 Bump3
// P4.3 Bump2
// P4.2 Bump1
// P4.0 Bump0, right side of robot

// Left motor direction connected to P5.4 (J3.29)
// Left motor PWM connected to P2.7/TA0CCP4 (J4.40)
// Left motor enable connected to P3.7 (J4.31)
// Right motor direction connected to P5.5 (J3.30)
// Right motor PWM connected to P2.6/TA0CCP3 (J4.39)
// Right motor enable connected to P3.6 (J2.11)

#include "msp.h"
#include "..\inc\bump.h"
#include "..\inc\Clock.h"
#include "..\inc\SysTick.h"
#include "..\inc\CortexM.h"
#include "..\inc\LaunchPad.h"
#include "..\inc\Motor.h"
#include "..\inc\TimerA1.h"
#include "..\inc\TExaS.h"

// Driver test
void TimedPause(uint32_t time){
  Clock_Delay1ms(time);          // run for a while and stop
  Motor_Stop();
  while(LaunchPad_Input()==0);  // wait for touch
  while(LaunchPad_Input());     // wait for release
}
int Program13_1(void){
  Clock_Init48MHz();
  LaunchPad_Init(); // built-in switches and LEDs
  Bump_Init();      // bump switches
  Motor_Init();     // your function
  while(1){
    TimedPause(4000);
    Motor_Forward(7500,7500);  // your function
    TimedPause(2000);
    Motor_Backward(7500,7500); // your function
    TimedPause(3000);
    Motor_Left(5000,5000);     // your function
    TimedPause(3000);
    Motor_Right(5000,5000);    // your function
  }
}

// Test of Periodic interrupt
#define REDLED (*((volatile uint8_t *)(0x42098060)))
#define BLUELED (*((volatile uint8_t *)(0x42098068)))
uint32_t Time;
void Task(void){
  REDLED ^= 0x01;       // toggle P2.0
  REDLED ^= 0x01;       // toggle P2.0
  Time = Time + 1;
  REDLED ^= 0x01;       // toggle P2.0
}
int Program13_2(void){
  Clock_Init48MHz();
  LaunchPad_Init();  // built-in switches and LEDs
  TimerA1_Init(&Task,500);  // 1000 Hz
  EnableInterrupts();
  while(1){
    BLUELED ^= 0x01; // toggle P2.1
  }
}

int main0(void){
    // write a main program that uses PWM to move the robot
    // like Program13_1, but uses TimerA1 to periodically
    // check the bump switches, stopping the robot on a collision
 
 
  while(1){
    
  }
}

