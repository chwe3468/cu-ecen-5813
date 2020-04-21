################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/System.c \
../source/buffer.c \
../source/command_parser.c \
../source/gpio.c \
../source/i2c.c \
../source/led.c \
../source/logger.c \
../source/mma8451.c \
../source/mtb.c \
../source/project_5.c \
../source/semihost_hardfault.c \
../source/state.c \
../source/test.c \
../source/timer.c \
../source/touch_sen.c 

OBJS += \
./source/System.o \
./source/buffer.o \
./source/command_parser.o \
./source/gpio.o \
./source/i2c.o \
./source/led.o \
./source/logger.o \
./source/mma8451.o \
./source/mtb.o \
./source/project_5.o \
./source/semihost_hardfault.o \
./source/state.o \
./source/test.o \
./source/timer.o \
./source/touch_sen.o 

C_DEPS += \
./source/System.d \
./source/buffer.d \
./source/command_parser.d \
./source/gpio.d \
./source/i2c.d \
./source/led.d \
./source/logger.d \
./source/mma8451.d \
./source/mtb.d \
./source/project_5.d \
./source/semihost_hardfault.d \
./source/state.d \
./source/test.d \
./source/timer.d \
./source/touch_sen.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DINCLUDE_LOGGING=1 -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/project_5/board" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/project_5/source" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/project_5" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/project_5/drivers" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/project_5/CMSIS" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/project_5/utilities" -I"/home/user/Documents/MCUXpresso_11.1.1_3241/workspace/project_5/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


