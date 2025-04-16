/*
 * opt_test.c
 *
 *  Created on: Apr 14, 2025
 *      Author: novik
 */

#include <stdio.h>
#include <stdint.h>
#include "msp.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/Bump.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/Clock.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/CortexM.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/I2CB1.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/LaunchPad.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/Motor.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/opt3101.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/SysTick.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/UART0.h"


#define CH  3
#define BASESPEED   5000
#define PWMMAX      14998
#define PWMMOVEMAX  14998
#define PWMMIN      0
#define PWMMOVEMIN  1000

uint32_t distance[CH];
uint32_t amplitude[CH];

int32_t desired = 0;
int32_t actual;
int32_t ek, ek_1;
int32_t integral;
int32_t derivative;
float turning_weight;
float alpha;
float filtered_actual = 0;
float speed_scaler = 1.0;

int32_t Kp = 6;
int32_t Ki = 0.22;
int32_t Kd = 0;

int32_t dutyk;
int32_t left_duty;
int32_t right_duty;
uint16_t base_left_duty = BASESPEED;
uint16_t base_right_duty = BASESPEED;


void readOPTSensor(void) {
    uint32_t i;
    for (i = 0; i < CH; i++) {
        //printf("starting measurement\n");
        OPT3101_StartMeasurementChannel(i);
        //printf("waiting for busy-wait\n");
        while(!OPT3101_CheckDistanceSensor()) {}
        //printf("busy wait complete\n");
        OPT3101_GetMeasurement(distance, amplitude);
        distance[i] = OPT3101_GetDistanceMillimeters();
//        printf("channel %d: %d\n", i, distance[i]);
    }
}

// side to side methodology: adjust towards whichever wall is farther
// if getting closer to something, TURN FASTER
void PID(void) {
    LaunchPad_Output(BLUE);
    // read distance measurement
    readOPTSensor();

    // calculate deviation and error
    actual = distance[0] - distance[2];
    filtered_actual = alpha*filtered_actual + (1-alpha)*actual;  // low pass filter
    ek = (int32_t)filtered_actual - desired;
    // forward obstacle interference deadzone
    if (abs(ek) < 150 && distance[1] < 200) ek = (ek>0) ? 150 : -150;
    else if (abs(ek) < 75 && distance[1] < 250) ek = (ek>0) ? 75 : -75;
    printf("error: %d\n", ek);

    // front proximity scale
    if (distance[1] < 100) turning_weight = 2.5;
    else if (distance[1] < 200) turning_weight = 2.0;
    else if (distance[1] < 300) turning_weight = 1.5;
    else turning_weight = 1.0;
    printf("turning weight: %f\n", turning_weight);

    // update PID terms
    integral += ek;
    derivative = ek - ek_1;
    ek_1 = ek;

    // control equation
    dutyk = Kp*turning_weight*ek + Ki*integral + Kd*derivative;
    //dutyk *= turning_weight;
    printf("controlled duty: %d\n", dutyk);

    // apply to PWM
    left_duty = base_left_duty + dutyk;
    right_duty = base_right_duty - dutyk;

    // PWM range clamping
    if (left_duty > PWMMOVEMAX) left_duty = PWMMOVEMAX;
    if (right_duty > PWMMOVEMAX) right_duty = PWMMOVEMAX;
    if (left_duty < PWMMOVEMIN) left_duty = PWMMOVEMIN;
    if (right_duty < PWMMOVEMIN) right_duty = PWMMOVEMIN;

    // update motors
    printf("left duty: %d,\tright_duty: %d\n", (uint16_t)left_duty, (uint16_t)right_duty);
    Motor_Forward((uint16_t)left_duty, (uint16_t)right_duty);
}


 int main(void) {

    Clock_Init48MHz();
    printf("hello\n");
    SysTick_Init();
    Bump_Init();
    Motor_Init();
    LaunchPad_Init();
    I2CB1_Init(30);
    OPT3101_Init();
    OPT3101_Setup();
    OPT3101_CalibrateInternalCrosstalk();

    printf("starting loop\n");
    while(1) {
        //Motor_Forward(base_left_duty, base_right_duty);
//        while (Bump_Read() == 0) {
            PID();
            LaunchPad_Output(GREEN);
            Clock_Delay1ms(100);
//        }
//        LaunchPad_Output(RED);
//        Motor_Stop();
    }
}

