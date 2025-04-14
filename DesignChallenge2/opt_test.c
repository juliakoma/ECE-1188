/*
 * opt_test.c
 *
 *  Created on: Apr 14, 2025
 *      Author: novik
 */

#include <stdio.h>
#include <stdint.h>
#include "msp.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/Clock.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/CortexM.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/I2CB1.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/LaunchPad.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/opt3101.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/SysTick.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc/UART0.h"

#define CH  3


 uint32_t distance[CH];

int main(void) {

    Clock_Init48MHz();
    SysTick_Init();
    I2CB1_Init(30);

    while(1) {
        uint32_t i;
        for (i = 0; i < CH; i++) {
            OPT3101_StartMeasurementChannel(i);
            while(!OPT3101_CheckDistanceSensor()) {}
            distance[i] = OPT3101_GetDistanceMillimeters();
            printf("%d\n", distance[i]);
        }
        SysTick_Wait10ms(100);
    }
}

