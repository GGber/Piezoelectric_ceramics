################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccs920/ccs/tools/compiler/ti-cgt-c2000_18.12.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./Hardware/DSP_ADC/dsp_adc.obj" \
"./Hardware/EPWM/epwm.obj" \
"./Hardware/FAN/fan_epwm.obj" \
"./Hardware/LED/led.obj" \
"./Hardware/Mcbsp/mcbsp.obj" \
"./Hardware/PID/con_pid.obj" \
"./Hardware/SCI/sci.obj" \
"./Hardware/System/system.obj" \
"./Lib/source/DSP2833x_ADC_cal.obj" \
"./Lib/source/DSP2833x_Adc.obj" \
"./Lib/source/DSP2833x_CodeStartBranch.obj" \
"./Lib/source/DSP2833x_CpuTimers.obj" \
"./Lib/source/DSP2833x_DefaultIsr.obj" \
"./Lib/source/DSP2833x_EPwm.obj" \
"./Lib/source/DSP2833x_GlobalVariableDefs.obj" \
"./Lib/source/DSP2833x_Gpio.obj" \
"./Lib/source/DSP2833x_Mcbsp.obj" \
"./Lib/source/DSP2833x_PieCtrl.obj" \
"./Lib/source/DSP2833x_PieVect.obj" \
"./Lib/source/DSP2833x_Sci.obj" \
"./Lib/source/DSP2833x_SysCtrl.obj" \
"./Lib/source/DSP2833x_usDelay.obj" \
"../Lib/cmd/DSP2833x_Headers_nonBIOS.cmd" \
"../Lib/cmd/F28335.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Hardware/DSP_ADC/subdir_vars.mk
-include Hardware/EPWM/subdir_vars.mk
-include Hardware/FAN/subdir_vars.mk
-include Hardware/LED/subdir_vars.mk
-include Hardware/Mcbsp/subdir_vars.mk
-include Hardware/PID/subdir_vars.mk
-include Hardware/SCI/subdir_vars.mk
-include Hardware/System/subdir_vars.mk
-include Lib/cmd/subdir_vars.mk
-include Lib/source/subdir_vars.mk
-include subdir_rules.mk
-include Hardware/DSP_ADC/subdir_rules.mk
-include Hardware/EPWM/subdir_rules.mk
-include Hardware/FAN/subdir_rules.mk
-include Hardware/LED/subdir_rules.mk
-include Hardware/Mcbsp/subdir_rules.mk
-include Hardware/PID/subdir_rules.mk
-include Hardware/SCI/subdir_rules.mk
-include Hardware/System/subdir_rules.mk
-include Lib/cmd/subdir_rules.mk
-include Lib/source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
PEC_GGber.out \

EXE_OUTPUTS__QUOTED += \
"PEC_GGber.out" \

BIN_OUTPUTS += \
PEC_GGber.hex \

BIN_OUTPUTS__QUOTED += \
"PEC_GGber.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "PEC_GGber.out"

# Tool invocations
PEC_GGber.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-c2000_18.12.3.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"PEC_GGber.map" --stack_size=0x300 --warn_sections -i"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-c2000_18.12.3.LTS/lib" -i"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-c2000_18.12.3.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="PEC_GGber_linkInfo.xml" --rom_model -o "PEC_GGber.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

PEC_GGber.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-c2000_18.12.3.LTS/bin/hex2000"  -o "PEC_GGber.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "Hardware\DSP_ADC\dsp_adc.obj" "Hardware\EPWM\epwm.obj" "Hardware\FAN\fan_epwm.obj" "Hardware\LED\led.obj" "Hardware\Mcbsp\mcbsp.obj" "Hardware\PID\con_pid.obj" "Hardware\SCI\sci.obj" "Hardware\System\system.obj" "Lib\source\DSP2833x_ADC_cal.obj" "Lib\source\DSP2833x_Adc.obj" "Lib\source\DSP2833x_CodeStartBranch.obj" "Lib\source\DSP2833x_CpuTimers.obj" "Lib\source\DSP2833x_DefaultIsr.obj" "Lib\source\DSP2833x_EPwm.obj" "Lib\source\DSP2833x_GlobalVariableDefs.obj" "Lib\source\DSP2833x_Gpio.obj" "Lib\source\DSP2833x_Mcbsp.obj" "Lib\source\DSP2833x_PieCtrl.obj" "Lib\source\DSP2833x_PieVect.obj" "Lib\source\DSP2833x_Sci.obj" "Lib\source\DSP2833x_SysCtrl.obj" "Lib\source\DSP2833x_usDelay.obj" 
	-$(RM) "main.d" "Hardware\DSP_ADC\dsp_adc.d" "Hardware\EPWM\epwm.d" "Hardware\FAN\fan_epwm.d" "Hardware\LED\led.d" "Hardware\Mcbsp\mcbsp.d" "Hardware\PID\con_pid.d" "Hardware\SCI\sci.d" "Hardware\System\system.d" "Lib\source\DSP2833x_Adc.d" "Lib\source\DSP2833x_CpuTimers.d" "Lib\source\DSP2833x_DefaultIsr.d" "Lib\source\DSP2833x_EPwm.d" "Lib\source\DSP2833x_GlobalVariableDefs.d" "Lib\source\DSP2833x_Gpio.d" "Lib\source\DSP2833x_Mcbsp.d" "Lib\source\DSP2833x_PieCtrl.d" "Lib\source\DSP2833x_PieVect.d" "Lib\source\DSP2833x_Sci.d" "Lib\source\DSP2833x_SysCtrl.d" 
	-$(RM) "Lib\source\DSP2833x_ADC_cal.d" "Lib\source\DSP2833x_CodeStartBranch.d" "Lib\source\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

