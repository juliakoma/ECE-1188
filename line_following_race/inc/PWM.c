// PWM.c
// Runs on MSP432
// PWM on P2.4 using TimerA0 TA0.CCR1
// PWM on P2.5 using TimerA0 TA0.CCR2
// PWM on P2.6 using TimerA0 TA0.CCR3
// PWM on P2.7 using TimerA0 TA0.CCR4
// MCLK = SMCLK = 3MHz DCO; ACLK = 32.768kHz
// TACCR0 generates a square wave of freq ACLK/1024 =32Hz
// Derived from msp432p401_portmap_01.c in MSPware
// Jonathan Valvano
// July 11, 2019

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

#include "msp.h"

//***************************PWM_Init1*******************************
// PWM outputs on P2.4
// Inputs:  period (166.67ns)
//          duty (0<=duty<period-1)
// Outputs: none
// SMCLK = 48MHz/4 = 12 MHz, 83.33ns
// Counter counts up to TA0CCR0 and back down
// Let Timerclock period T = 1/12MHz = 83.33ns
// P2.4=1 when timer equals TA0CCR1 on way down, P2.4=0 when timer equals TA0CCR1 on way up
// Period of P2.4 is period*166.67ns, duty cycle is duty/period
void PWM_Init1(uint16_t period, uint16_t duty){
  if(duty >= period) return;     // bad input
  P2->DIR |= 0x10;               // P2.4 output
  P2->SEL0 |= 0x10;              // P2.4 Timer0A functions
  P2->SEL1 &= ~0x10;             // P2.4 Timer0A functions
  TIMER_A0->CCTL[0] = 0x0080;    // CCI0 toggle
  TIMER_A0->CCR[0] = period;     // Period is 2*period*8*83.33ns is 1.333*period
  TIMER_A0->EX0 = 0x0000;        //    divide by 1
  TIMER_A0->CCTL[1] = 0x0040;    // CCR1 toggle/reset
  TIMER_A0->CCR[1] = duty;       // CCR1 duty cycle is duty1/period
  TIMER_A0->CTL = 0x0230;        // SMCLK=12MHz, divide by 1, up-down mode
// bit  mode
// 9-8  10    TASSEL, SMCLK=12MHz
// 7-6  00    ID, divide by 1
// 5-4  11    MC, up-down mode
// 2    0     TACLR, no clear
// 1    0     TAIE, no interrupt
// 0          TAIFG
}
//***************************PWM_Init12*******************************
// PWM outputs on P2.4, P2.5
// Inputs:  period (1.333us)
//          duty1
//          duty2
// Outputs: none
// SMCLK = 48MHz/4 = 12 MHz, 83.33ns
// Counter counts up to TA0CCR0 and back down
// Let Timerclock period T = 8/12MHz = 666.7ns
// P2.4=1 when timer equals TA0CCR1 on way down, P2.4=0 when timer equals TA0CCR1 on way up
// P2.5=1 when timer equals TA0CCR2 on way down, P2.5=0 when timer equals TA0CCR2 on way up
// Period of P2.4 is period*1.333us, duty cycle is duty1/period
// Period of P2.5 is period*1.333us, duty cycle is duty2/period
void PWM_Init12(uint16_t period, uint16_t duty1, uint16_t duty2){
  if(duty1 >= period) return; // bad input
  if(duty2 >= period) return; // bad input
  P2->DIR |= 0x30;          // P2.4, P2.5 output
  P2->SEL0 |= 0x30;         // P2.4, P2.5 Timer0A functions
  P2->SEL1 &= ~0x30;        // P2.4, P2.5 Timer0A functions
  TIMER_A0->CCTL[0] = 0x0080;      // CCI0 toggle
  TIMER_A0->CCR[0] = period;       // Period is 2*period*8*83.33ns is 1.333*period
  TIMER_A0->EX0 = 0x0000;        //    divide by 1
  TIMER_A0->CCTL[1] = 0x0040;      // CCR1 toggle/reset
  TIMER_A0->CCR[1] = duty1;        // CCR1 duty cycle is duty1/period
  TIMER_A0->CCTL[2] = 0x0040;      // CCR2 toggle/reset
  TIMER_A0->CCR[2] = duty2;        // CCR2 duty cycle is duty2/period
  TIMER_A0->CTL = 0x02F0;        // SMCLK=12MHz, divide by 8, up-down mode
// bit  mode
// 9-8  10    TASSEL, SMCLK=12MHz
// 7-6  11    ID, divide by 8
// 5-4  11    MC, up-down mode
// 2    0     TACLR, no clear
// 1    0     TAIE, no interrupt
// 0          TAIFG
}

//***************************PWM_Duty1*******************************
// change duty cycle of PWM output on P2.4
// Inputs:  duty1
// Outputs: none
// period of P2.4 is 2*period*666.7ns, duty cycle is duty1/period
void PWM_Duty1(uint16_t duty1){
  if(duty1 >= TIMER_A0->CCR[0]) return; // bad input
  TIMER_A0->CCR[1] = duty1;        // CCR1 duty cycle is duty1/period
}

//***************************PWM_Duty2*******************************
// change duty cycle of PWM output on P2.5
// Inputs:  duty2
// Outputs: none// period of P2.5 is 2*period*666.7ns, duty cycle is duty2/period
void PWM_Duty2(uint16_t duty2){
  if(duty2 >= TIMER_A0->CCR[0]) return; // bad input
  TIMER_A0->CCR[2] = duty2;        // CCR2 duty cycle is duty2/period
}

//***************************PWM_Init34*******************************
// PWM outputs on P2.6, P2.7
// Inputs:  period (1.333us)
//          duty3
//          duty4
// Outputs: none
// SMCLK = 48MHz/4 = 12 MHz, 83.33ns
// Counter counts up to TA0CCR0 and back down
// Let Timerclock period T = 8/12MHz = 666.7ns
// period of P7.3 squarewave is 4*period*666.7ns
// P2.6=1 when timer equals TA0CCR3 on way down, P2.6=0 when timer equals TA0CCR3 on way up
// P2.7=1 when timer equals TA0CCR4 on way down, P2.7=0 when timer equals TA0CCR4 on way up
// Period of P2.6 is period*1.333us
// Duty cycle of P2.6 is duty3/period
// Period of P2.7 is period*1.333us
// Duty cycle of P2.7 is duty4/period
void PWM_Init34(uint16_t period, uint16_t duty3, uint16_t duty4){
    // write this as part of Lab 13
    if (duty3 >= period || duty4 >= period) return;
    
  P2->DIR |= 0xC0;          // P2.6, P2.7 output
  P2->SEL0 |= 0xC0;         // P2.6, P2.7 Timer0A functions
  P2->SEL1 &= ~0xC0;        // P2.6, P2.7 Timer0A functions

  TIMER_A0->CCTL[0] = 0x0080;   // CCI0 toggle
  TIMER_A0->CCR[0] = period;    
  TIMER_A0->EX0 = 0x0000;       // /1
  TIMER_A0->CCTL[3] = 0x0040;   // toggle/reset
  TIMER_A0->CCR[3] = duty3;     // set duty cycle for left motor in sub module 3
  TIMER_A0->CCTL[4] = 0x0040;   // toggle/reset
  TIMER_A0->CCR[4] = duty4;     // set duty cycle for right motor in sub module 4
  TIMER_A0->CTL = 0x02F0;       // SMCLK, /8, up-down mode

}

//***************************PWM_Duty3*******************************
// change duty cycle of PWM output on P2.6
// Inputs:  duty3
// Outputs: none
// period of P2.6 is 2*period*666.7ns
// duty cycle is duty3/period
void PWM_Duty3(uint16_t duty3){
    // write this as part of Lab 13
    if (duty3 >= TIMER_A0->CCR[0]) return;
    TIMER_A0->CCR[3] = duty3;  
}

//***************************PWM_Duty4*******************************
// change duty cycle of PWM output on P2.7
// Inputs:  duty4
// Outputs: none// period of P2.7 is 2*period*666.7ns
// duty cycle is duty2/period
void PWM_Duty4(uint16_t duty4){
    // write this as part of Lab 13
    if (duty4 >= TIMER_A0->CCR[0]) return;
    TIMER_A0->CCR[4] = duty4;  
}

//***************************PWM_RobotArmInit*******************************
// PWM outputs on P2.4/PM_TA0.1 (PMAP from TA1.1), P3.5/PM_UCB2CLK (PMAP from TA1.2), and P5.7/TA2.2/VREF-/VeREF-/C1.6
// Inputs:  period (333.33ns)
//          duty0 (0<=duty0<period-1)
//          duty1 (0<=duty1<period-1)
//          duty2 (0<=duty2<period-1)
// Outputs: none
// SMCLK = 48MHz/4 = 12 MHz, 83.33ns
// Use clock divider of 2 to get timer clock period 166.67ns
// Counter counts up to TAnCCR0 and back down
// Let Timerclock period T = 2/12MHz = 166.67nsns
// P2.4=1 when timer equals TA1CCR1 on way down, P2.4=0 when timer equals TA1CCR1 on way up
// P3.5=1 when timer equals TA1CCR2 on way down, P3.5=0 when timer equals TA1CCR2 on way up
// P5.7=1 when timer equals TA2CCR2 on way down, P5.7=0 when timer equals TA2CCR2 on way up
// Period of P2.4 is period*333.33ns, duty cycle is duty0/period
// Period of P3.5 is period*333.33ns, duty cycle is duty1/period
// Period of P5.7 is period*333.33ns, duty cycle is duty2/period
void PWM_RobotArmInit(uint16_t period, uint16_t duty0, uint16_t duty1, uint16_t duty2){
  if(duty0 >= period) return;    // bad input
  if(duty1 >= period) return;    // bad input
  if(duty2 >= period) return;    // bad input
  TIMER_A1->CTL &= ~0x0030;      // halt TimerA1 while port mapping is in progress
  PMAP->KEYID = 0x2D52;          // write key to unlock write access to PMAP registers
  PMAP->CTL = 0x0002;            // allow reconfiguration of port mapping (in case needed in another module)
  P2MAP->PMAP_REGISTER4 = PMAP_TA1CCR1A;// configure P2.4 as TA1.1
  P2->DIR |= 0x10;               // P2.4 output
  P2->SEL0 |= 0x10;              // P2.4 PMAP functions
  P2->SEL1 &= ~0x10;             // P2.4 PMAP functions
  P3MAP->PMAP_REGISTER5 = PMAP_TA1CCR2A;// configure P3.5 as TA1.2
  P3->DIR |= 0x20;               // P3.5 output
  P3->SEL0 |= 0x20;              // P3.5 PMAP functions
  P3->SEL1 &= ~0x20;             // P3.5 PMAP functions
  PMAP->KEYID = 0x0000;          // write incorrect key to lock write access to PMAP registers
  TIMER_A1->CCTL[0] = 0x0080;    // CCI0 toggle
  TIMER_A1->CCR[0] = period - 1; // Period is 2*period*8*166.67ns is 2.666*period
  TIMER_A1->EX0 = 0x0000;        //    divide by 1
  TIMER_A1->CCTL[1] = 0x0040;    // CCR1 toggle/reset
  TIMER_A1->CCR[1] = duty0;      // CCR1 duty cycle is duty0/period
  TIMER_A1->CCTL[2] = 0x0040;    // CCR2 toggle/reset
  TIMER_A1->CCR[2] = duty1;      // CCR2 duty cycle is duty1/period
  TIMER_A1->CTL = 0x0270;        // SMCLK=12MHz, divide by 2, up-down mode
// bit  mode
// 9-8  10    TASSEL, SMCLK=12MHz
// 7-6  01    ID, divide by 2
// 5-4  11    MC, up-down mode
// 2    0     TACLR, no clear
// 1    0     TAIE, no interrupt
// 0          TAIFG
  P5->DIR |= 0x80;               // P5.7 output
  P5->SEL0 |= 0x80;              // P5.7 TimerA2.2 functions
  P5->SEL1 &= ~0x80;             // P5.7 TimerA2.2 functions
  TIMER_A2->CCTL[0] = 0x0080;    // CCI0 toggle
  TIMER_A2->CCR[0] = period - 1; // Period is 2*period*8*166.67ns is 2.666*period
  TIMER_A2->EX0 = 0x0000;        //    divide by 1
  TIMER_A2->CCTL[2] = 0x0040;    // CCR2 toggle/reset
  TIMER_A2->CCR[2] = duty2;      // CCR2 duty cycle is duty2/period
  TIMER_A2->CTL = 0x0270;        // SMCLK=12MHz, divide by 2, up-down mode
// bit  mode
// 9-8  10    TASSEL, SMCLK=12MHz
// 7-6  01    ID, divide by 2
// 5-4  11    MC, up-down mode
// 2    0     TACLR, no clear
// 1    0     TAIE, no interrupt
// 0          TAIFG
}

//***************************PWM_RobotArmDuty0*******************************
// change duty cycle of PWM output on P2.4
// Inputs:  duty0
// Outputs: none
// Period of P2.4 is period*333.33ns, duty cycle is duty0/period
void PWM_RobotArmDuty0(uint16_t duty0){
  if(duty0 >= TIMER_A1->CCR[0]) return; // bad input
  TIMER_A1->CCR[1] = duty0;      // CCR1 duty cycle is duty0/period
}

//***************************PWM_RobotArmGetDuty0*******************************
// get the duty cycle of PWM output on P2.4
// Inputs: none
// Outputs: duty0
// Period of P2.4 is period*333.33ns, duty cycle is duty0/period
uint16_t PWM_RobotArmGetDuty0(void){
  return TIMER_A1->CCR[1];       // CCR1 duty cycle is duty0/period
}

//***************************PWM_RobotArmDuty1*******************************
// change duty cycle of PWM output on P3.5
// Inputs:  duty1
// Outputs: none
// Period of P3.5 is period*333.33ns, duty cycle is duty1/period
void PWM_RobotArmDuty1(uint16_t duty1){
  if(duty1 >= TIMER_A1->CCR[0]) return; // bad input
  TIMER_A1->CCR[2] = duty1;      // CCR2 duty cycle is duty1/period
}

//***************************PWM_RobotArmGetDuty1*******************************
// get the duty cycle of PWM output on P3.5
// Inputs: none
// Outputs: duty1
// Period of P3.5 is period*333.33ns, duty cycle is duty1/period
uint16_t PWM_RobotArmGetDuty1(void){
  return TIMER_A1->CCR[2];       // CCR2 duty cycle is duty1/period
}

//***************************PWM_RobotArmDuty2*******************************
// change duty cycle of PWM output on P5.7
// Inputs:  duty2
// Outputs: none
// Period of P5.7 is period*333.33ns, duty cycle is duty2/period
void PWM_RobotArmDuty2(uint16_t duty2){
  if(duty2 >= TIMER_A2->CCR[0]) return; // bad input
  TIMER_A2->CCR[2] = duty2;      // CCR2 duty cycle is duty2/period
}

//***************************PWM_RobotArmGetDuty2*******************************
// get the duty cycle of PWM output on P5.7
// Inputs: none
// Outputs: duty2
// Period of P5.7 is period*333.33ns, duty cycle is duty2/period
uint16_t PWM_RobotArmGetDuty2(void){
  return TIMER_A2->CCR[2];       // CCR2 duty cycle is duty2/period
}

