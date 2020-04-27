################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

OBJS += \
./utilities/fsl_debug_console.o 

C_DEPS += \
./utilities/fsl_debug_console.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DDEBUG -DFSL_RTOS_FREE_RTOS -DFRDM_KL25Z -DFREEDOM -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/frdmkl25z_rtos_examples_freertos_swtimer/board" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/frdmkl25z_rtos_examples_freertos_swtimer/source" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/frdmkl25z_rtos_examples_freertos_swtimer" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/frdmkl25z_rtos_examples_freertos_swtimer/drivers" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/frdmkl25z_rtos_examples_freertos_swtimer/CMSIS" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/frdmkl25z_rtos_examples_freertos_swtimer/utilities" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/frdmkl25z_rtos_examples_freertos_swtimer/freertos" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/frdmkl25z_rtos_examples_freertos_swtimer/startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


