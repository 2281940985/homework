################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
User/%.obj: ../User/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/CCS/CCS1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/time" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/rs485" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/tlv5620" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/24cxx" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/iic" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/spi" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/uart" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/adc" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/epwm" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/exti" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/key" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/leds" --include_path="E:/CCSproject/DSP2833x_Libraries/DSP2833x_common/include" --include_path="E:/CCSproject/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="E:/CCSproject/DSP2833x_Example/DSP2883351111/APP/smg" --include_path="D:/CCS/CCS1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="User/$(basename $(<F)).d_raw" --obj_directory="User" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


