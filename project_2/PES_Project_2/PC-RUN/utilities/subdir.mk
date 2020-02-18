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
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DINCLUDE_LOGGING=1 -DSDK_DEBUGCONSOLE=1 -DPC_RUN=1 -I"/home/user/ecen5813/cu-ecen-5813/project_2/PES_Project_2/board" -I"/home/user/ecen5813/cu-ecen-5813/project_2/PES_Project_2/source" -I"/home/user/ecen5813/cu-ecen-5813/project_2/PES_Project_2" -I"/home/user/ecen5813/cu-ecen-5813/project_2/PES_Project_2/CMSIS" -I"/home/user/ecen5813/cu-ecen-5813/project_2/PES_Project_2/utilities" -I"/home/user/ecen5813/cu-ecen-5813/project_2/PES_Project_2/startup" -I"/home/user/ecen5813/cu-ecen-5813/project_2/PES_Project_2/drivers" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

