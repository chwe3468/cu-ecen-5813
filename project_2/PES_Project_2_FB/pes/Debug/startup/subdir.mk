################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl25z4.c 

OBJS += \
./startup/startup_mkl25z4.o 

C_DEPS += \
./startup/startup_mkl25z4.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DINCLUDE_LOGGING=1 -DINCLUDE_LOG_DEBUG=1 -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/pes/board" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/pes/source" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/pes" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/pes/drivers" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/pes/CMSIS" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/pes/utilities" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/pes/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


