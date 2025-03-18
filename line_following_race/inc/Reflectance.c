
// Reflectance.c
// Updated with reduced delays for faster sensor updates

#include <stdint.h>
#include "msp432.h"
#include "..\inc\Clock.h"

// Initialize the GPIO pins associated with the reflectance sensor
void Reflectance_Init(void){
    // P5.3 and P9.2 for LED illumination
    P5->SEL0 &= ~0x08;  // P5.3
    P5->SEL1 &= ~0x08;
    P5->DIR |= 0x08;
    P5->OUT &= ~0x08;

    P9->SEL0 &= ~0x04;  // P9.2
    P9->SEL1 &= ~0x04;
    P9->DIR |= 0x04;
    P9->OUT &= ~0x04;

    // P7 for sensor inputs
    P7->SEL0 = 0x00;
    P7->SEL1 = 0x00;
    P7->DIR = 0x00;
}

// Read the eight sensors with a reduced charge pulse delay
uint8_t Reflectance_Read(uint32_t time){
    uint8_t result;

    P5->OUT |= 0x08;
    P9->OUT |= 0x04;

    P7->OUT |= 0xFF;
    P7->DIR |= 0xFF;
    Clock_Delay1us(5); // Reduced from 10us to 5us

    P7->DIR = 0x00;
    Clock_Delay1us(time);  // Integration delay provided by caller (now 1000us)

    result = P7->IN; // Read sensor values

    P5->OUT &= ~0x08;
    P9->OUT &= ~0x04;

    UART0_OutUHex(result); // Debug output
    return result;
}

// Compute the integrated line position from sensor data
int32_t Reflectance_Position(uint8_t data){
    int32_t weights[8] = {-33400,-23800,-14300,-4800,4800,14300,23800,33400};
    int32_t numerator = 0;
    int32_t denominator = 0;
    int i;
    for (i = 0; i < 8; i++){
        if (data & (1 << i)){
            numerator += weights[i];
            denominator += 1;
        }
    }
    if (denominator == 0){
        return 0;
    }
    return (numerator / denominator);
}

//int32_t Reflectance_Position(uint8_t data) {
//    int32_t numerator = 0;
//    int32_t denominator = 0;
//    int i;
//
//    // Check if both outer sensors (sensor 1 and sensor 8) are active.
//    // Bit 0 corresponds to sensor 1 (rightmost) and bit 7 corresponds to sensor 8 (leftmost).
//    if ((data & 0x81) == 0x81) {
//        // Use only the middle sensors (sensors 2 through 7; bits 1..6).
//        // Define new weights for these sensors.
//        int32_t midWeights[6] = {-23800, -14300, -4800, 4800, 14300, 23800};
//        for (i = 0; i < 6; i++) {
//            // Sensor bit for sensor (i+2) is (1 << (i+1))
//            if (data & (1 << (i + 1))) {
//                numerator += midWeights[i];
//                denominator += 1;
//            }
//        }
//    } else {
//        // Normal operation: use all 8 sensors with the standard weights.
//        int32_t weights[8] = {-33400, -23800, -14300, -4800, 4800, 14300, 23800, 33400};
//        for (i = 0; i < 8; i++) {
//            if (data & (1 << i)) {
//                numerator += weights[i];
//                denominator += 1;
//            }
//        }
//    }
//
//    if (denominator == 0) {
//        return 0;  // No line detected
//    }
//    return numerator / denominator;
//}


void Reflectance_Start(void){
    P5->OUT |= 0x08;
    P9->OUT |= 0x04;

    P7->OUT |= 0xFF;
    P7->DIR |= 0xFF;
    Clock_Delay1us(5); // Reduced delay here as well
    P7->DIR = 0x00;
}

uint8_t Reflectance_End(void){
    uint8_t sensorData;
    sensorData = P7->IN;
    P5->OUT &= ~0x08;
    P9->OUT &= ~0x04;
    return sensorData;
}
