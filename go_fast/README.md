# Robot Go Brr
### Speed Demons
Seth Blain, Julia Koma, Lizza Novikova <br> <br>

Source and implementation code for the Design Project 1 Line Following Robot.
## Module and Supplementary Files:
- `BumpInt.c` and `BumpInt.h`: Source and header files containing the edge-triggered interrupt bump sensor code.
- `Clock.c` and `Clock.h`: Source and header files containing system bus clock usage code.
- `CortexM.c` and `CortexM.h`: Source and header files containing the CortexM-based interrupt implementations
- `LaunchPad.c` and `LaunchPad.h`: Source and header files allowing for GPIO interfacing of the MPS432 LaunchPad.
- `Motor.c` and `Motor.h`: Source and header files containing PWM-based motor control code.
- `PWM.c` and `PWM.h`: Source and header files containing the hardware timer implemented PWM control
- `Reflectance.c` and `Reflectance.h`: Source and header files containing the initialization and implementation of the QTRX Sensor array to allow for line tracking.
- `UART0.c` and `UART0.h`: Source and header files containg UART communication implementation, used for debugging.
## Main File
- `fast_main.c`: Final implementation of the fully integrated system, encompassing the FSM the robot operates on and all of the above elements.

![gotta go fast](sanic.png)
