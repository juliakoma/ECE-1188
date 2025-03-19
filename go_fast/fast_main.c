// ECE 1188
// Line Following Race FSM
// Seth Blain, Julia Koma, Lizza Novikova

/* next steps???:
 * > state transitions feel behind, as if they are operating on previous state logic
 *   and not updating to current state when expected, may be imagining this tho lol.
     could keep current state transition logic as is, and also add a 'state execute'
     function to occur after the state transition occurs

 * > adjust wheel ratio when turning to allow for variable turn speeds/angles based on error

 * >
 */


#include <stdint.h>
#include "msp.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc\BumpInt.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc\Clock.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc\CortexM.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc\LaunchPad.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc\Motor.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc\PWM.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc\Reflectance.h"
#include "..\..\..\..\..\..\..\..\ti\tirslk_max_1_00_02\inc\UART0.h"


#define CHECK_NUM 2


// FSM States
typedef enum {
    IDLE,
    START,
    FORWARD,
    SPRINT,
    MILD_LEFT,
    MILD_RIGHT,
    SHARP_LEFT,
    SHARP_RIGHT,
    STOP
} State_t;

typedef struct {
    State_t arr[CHECK_NUM];
    uint8_t front;
    uint8_t rear;
} Queue;

State_t currentState = IDLE;
uint8_t CollisionFlag = 0;  // Flag for collision detection
Queue stateQueue;

// Function prototypes
void initQueue(Queue* q);
void enqueue(Queue* q, State_t state);
void dequeue(Queue* q);
void addState(void);
State_t checkState(Queue* q, uint8_t idx);
void FSM_Update(void);
void Sensor_Init(void);
uint8_t Read_Line_Sensors(void);
void HandleCollision(uint8_t bumpSensor);
void WaitForButtonPress(void);
int32_t Read_Line_Position(void);

// Initializes queue with idle states
// this may have to be reworked
// I haven't actually looked at how the queue stores the states
// and if it does it successfully or not
// type conversion of front var from signed to unsigned here may be strange
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = 0;
    enqueue(q, IDLE);
    enqueue(q, IDLE);
}

// FIFO add
void enqueue(Queue* q, State_t state) {
    q->arr[q->rear] = state;
    q->rear++;
}

// FIFO remove
void dequeue(Queue* q) {
    q->front++;
}

// Remove oldest state from queue and add current state
void addState() {
    dequeue(&stateQueue);
    enqueue(&stateQueue, currentState);
}

// Check state held at the index specified of the queue
State_t checkState(Queue* q, uint8_t idx) {
    return q->arr[q->front+idx];
}

// Initialize Sensors
void Sensor_Init(void) {
    Reflectance_Init();
    BumpInt_Init(&HandleCollision);  // Use bump sensor interrupts
}

// Read Line Sensors with an increased integration delay (from 1000us to 1500us)
uint8_t Read_Line_Sensors(void) {
    return Reflectance_Read(1200);
}

// Read Line Position using the integrated sensor value
int32_t Read_Line_Position(void) {
    return Reflectance_Position(Read_Line_Sensors());
}

// Handle Bump Collision
void HandleCollision(uint8_t bumpSensor) {
    Motor_Stop();   // Stop immediately
    CollisionFlag = 1; // Set collision flag
    UART0_OutString("Collision detected! Stopping...\n\r");
}

// Wait for Button Press with a moderate debounce delay
void WaitForButtonPress(void) {
    UART0_OutString("Press SW2 (P1.4) to start...\n\r");
    P1->DIR &= ~0x10;  // Set P1.4 as input
    P1->REN |= 0x10;   // Enable pull-up resistor
    P1->OUT |= 0x10;   // Set as pull-up

    while ((P1->IN & 0x10) != 0);  // Wait for SW2 press
    Clock_Delay1ms(10);            // Debounce delay
    while ((P1->IN & 0x10) == 0);    // Wait for SW2 release
}


// In your FSM_Update:
void FSM_Update(void) {
    static uint32_t startTime = 0;
    int32_t sensorData = Read_Line_Position();

    if (CollisionFlag) {
        CollisionFlag = 0;
        currentState = STOP;
        return;
    }

    switch (currentState) {
        case IDLE:
            WaitForButtonPress();
            currentState = START;
            //currentState = FORWARD;
            startTime = 0;
            break;

        case START:
            addState();
            Motor_Forward(6000, 6000);
            startTime += 80;
            if (startTime >= 1500) {  // After 2 seconds, switch to normal mode
                currentState = FORWARD;
            }
            break;
            //-33400,-23800,-14300,-4800,4800,14300,23800,33400
            // sensor:   0    1    2    3    4    5     6     7
            //          332, 237, 142, 47, -47, -142, -237, -332
        case FORWARD:
            addState();
            if(sensorData == -47 || sensorData == -189) {           // 4 or 4&5 activated
                currentState = MILD_LEFT;
            } else if(sensorData == 47 || sensorData == 189) {      // 3 or 3%2 activated
                currentState = MILD_RIGHT;
            } else if(sensorData == -142 || sensorData < -189) {    // 5-7 activated
                currentState = SHARP_LEFT;
            } else if(sensorData == 142 || sensorData > 189) {      // 0-2 activated
                currentState = SHARP_RIGHT;
            } else if (checkState(&stateQueue, 1) == FORWARD && checkState(&stateQueue, 2) == FORWARD) {
                currentState = SPRINT;
            } else {
                Motor_Forward(5000, 5000);
            }
            break;

        case SPRINT:
            addState();
//            if(sensorData == -47 || sensorData == -189) {           // 4 or 4&5 activated
//                currentState = MILD_LEFT;
//           } else if(sensorData == 47 || sensorData == 189) {      // 3 or 3%2 activated
//                currentState = MILD_RIGHT;
           if(sensorData == -142 || sensorData < -189) {    // 5-7 activated
                currentState = SHARP_LEFT;
           } else if(sensorData == 142 || sensorData > 189) {      // 0-2 activated
                currentState = SHARP_RIGHT;
           } else {
               Motor_Forward(10000, 10000);
           }
           break;

        case MILD_LEFT:
            addState();
            sensorData = Read_Line_Position();
            //Motor_Left(2500, 2525);
            Motor_Forward(3000, 5000);      // 3:5 wheel turn ratio
            if(sensorData > -47) {
                currentState = FORWARD;
            } else if (sensorData == -142 || sensorData < -189) {
                currentState = SHARP_LEFT;
            }
            break;

        case MILD_RIGHT:
            addState();
            sensorData = Read_Line_Position();
            //Motor_Right(2525, 2500);
            Motor_Forward(5000, 3000);  // 3500, 2100 (<- last used value), 3:5 wheel turn ratio
            if(sensorData < 47) {
                currentState = FORWARD;
            } else if (sensorData == 142 || sensorData > 189) {
                currentState = SHARP_RIGHT;
            }
            break;

        case SHARP_LEFT:
            addState();
            Motor_Forward(0, 5000);
            if(sensorData == -189 || sensorData == -47) {
                currentState = MILD_LEFT;
            } else if (sensorData == 142 || sensorData > 189) {
                currentState = SHARP_RIGHT;
            }
            break;

        case SHARP_RIGHT:
            addState();
            Motor_Forward(5000, 0);
            if(sensorData == 189 || sensorData == 47) {
                currentState = MILD_RIGHT;
            } else if (sensorData == -142 || sensorData < -189) {
                currentState = SHARP_LEFT;
            }
            break;

        case STOP:
            UART0_OutString("Robot stopped.\n\r");
            Motor_Stop();
            while (1);
    }
}


// Main Function with a moderate update delay (20ms)
int main(void) {
    Clock_Init48MHz();
    UART0_Init();
    Sensor_Init(); // Bump and Reflectance
    Motor_Init();
    EnableInterrupts();
    initQueue(&stateQueue);

    while (1) {
        FSM_Update();
        Clock_Delay1ms(10);  // Update FSM every 20ms
        // change delay value when adjust speed
        // higher motor speed may require more frequent state updates
    }
}
