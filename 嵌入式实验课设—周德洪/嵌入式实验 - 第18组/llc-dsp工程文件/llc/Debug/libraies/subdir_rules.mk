################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
libraies/DSP2833x_ADC_cal.obj: ../libraies/DSP2833x_ADC_cal.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_ADC_cal.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_Adc.obj: ../libraies/DSP2833x_Adc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_Adc.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_CodeStartBranch.obj: ../libraies/DSP2833x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_CodeStartBranch.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_CpuTimers.obj: ../libraies/DSP2833x_CpuTimers.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_CpuTimers.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_DefaultIsr.obj: ../libraies/DSP2833x_DefaultIsr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_DefaultIsr.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_EPwm.obj: ../libraies/DSP2833x_EPwm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_EPwm.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_GlobalVariableDefs.obj: ../libraies/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_GlobalVariableDefs.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_Gpio.obj: ../libraies/DSP2833x_Gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_Gpio.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_PieCtrl.obj: ../libraies/DSP2833x_PieCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_PieCtrl.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_PieVect.obj: ../libraies/DSP2833x_PieVect.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_PieVect.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_Sci.obj: ../libraies/DSP2833x_Sci.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_Sci.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_Spi.obj: ../libraies/DSP2833x_Spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_Spi.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_SysCtrl.obj: ../libraies/DSP2833x_SysCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_SysCtrl.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

libraies/DSP2833x_usDelay.obj: ../libraies/DSP2833x_usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="libraies/DSP2833x_usDelay.pp" --obj_directory="libraies" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


