// BumpInt.c
// Runs on MSP432, interrupt version
// Provides low-level functions to interface bump switches on the robot.
// Daniel Valvano and Jonathan Valvano
// July 11, 2019

#include <stdint.h>
#include "msp.h"

#define BUMP_MASK 0xDC  // Correct mask for P4.7, P4.6, P4.5, P4.3, P4.2, P4.0

static void (*BumpTask)(uint8_t) = 0;  // Function pointer for interrupt handler

// Initialize Bump sensors
// Configure P4.7, P4.6, P4.5, P4.3, P4.2, P4.0 as inputs with pull-up resistors
// Enable falling edge interrupt
void BumpInt_Init(void(*task)(uint8_t)){
    BumpTask = task; // Store user-defined function pointer
    P4->SEL0 &= ~BUMP_MASK;  // Clear function select for bump sensor pins
    P4->SEL1 &= ~BUMP_MASK;
    P4->DIR  &= ~BUMP_MASK;  // Set as inputs
    P4->REN  |= BUMP_MASK;   // Enable pull-up resistors
    P4->OUT  |= BUMP_MASK;   // Set resistors to pull-up mode
    P4->IES  |= BUMP_MASK;   // Interrupt on falling edge (active low)
    P4->IFG  &= ~BUMP_MASK;  // Clear interrupt flags
    P4->IE   |= BUMP_MASK;   // Enable interrupts
    NVIC->ISER[1] = 1 << ((PORT4_IRQn) & 31);  // Enable Port 4 interrupt in NVIC
}

// Read current state of bump sensors
// Returns 6-bit positive logic result (0 to 63)
uint8_t Bump_Read(void){
    uint8_t bump = (~P4->IN) & BUMP_MASK; // Invert logic (pressed = 1)
    return (bump >> 2) & 0x3F;  // Shift bits down to 6-bit format
}

// Port 4 ISR triggered on bump sensor activation
void PORT4_IRQHandler(void){
    uint8_t status = (P4->IFG & BUMP_MASK); // Get only bump sensor interrupts
    P4->IFG &= ~BUMP_MASK;  // Clear only bump sensor interrupt flags
    if (BumpTask) {
        BumpTask((status >> 2) & 0x3F);  // Pass 6-bit result
    }
}
