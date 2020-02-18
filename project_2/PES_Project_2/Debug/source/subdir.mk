################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/PES_Project_2.c \
../source/gpio.c \
../source/led.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/timer.c 

OBJS += \
./source/PES_Project_2.o \
./source/gpio.o \
./source/led.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/timer.o 

C_DEPS += \
./source/PES_Project_2.d \
./source/gpio.d \
./source/led.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/timer.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/PES_Project_2/board" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/PES_Project_2/source" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/PES_Project_2" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/PES_Project_2/CMSIS" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/PES_Project_2/utilities" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/PES_Project_2/startup" -I"/home/chutao/Documents/MCUXpresso_11.1.0_3209/workspace/PES_Project_2/drivers" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

