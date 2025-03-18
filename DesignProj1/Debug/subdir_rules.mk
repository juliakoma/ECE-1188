################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
BumpInt.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/BumpInt.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="BumpInt.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Clock.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Clock.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CortexM.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/CortexM.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="CortexM.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FlashProgram.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/FlashProgram.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FlashProgram.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="LaunchPad.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Motor.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/Motor.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Motor.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

PWM.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/PWM.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="PWM.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Reflectance.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/Reflectance.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Reflectance.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TExaS.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/TExaS.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="TExaS.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TimerA1.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/TimerA1.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="TimerA1.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

blinker.obj: C:/Users/julia/Documents/Cyber\ Phys/Projects/tirslk_max_1_00_02/inc/blinker.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1260/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/julia/Documents/Cyber Phys/Projects/tirslk_max_1_00_02/DesignProj1" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="blinker.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


