################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/System.c \
../source/buffer.c \
../source/command_parser.c \
../source/gpio.c \
../source/led.c \
../source/logger.c \
../source/mtb.c \
../source/project_5.c \
../source/semihost_hardfault.c \
../source/test.c \
../source/timer.c \
../source/touch_sen.c 

OBJS += \
./source/System.o \
./source/buffer.o \
./source/command_parser.o \
./source/gpio.o \
./source/led.o \
./source/logger.o \
./source/mtb.o \
./source/project_5.o \
./source/semihost_hardfault.o \
./source/test.o \
./source/timer.o \
./source/touch_sen.o 

C_DEPS += \
./source/System.d \
./source/buffer.d \
./source/command_parser.d \
./source/gpio.d \
./source/led.d \
./source/logger.d \
./source/mtb.d \
./source/project_5.d \
./source/semihost_hardfault.d \
./source/test.d \
./source/timer.d \
./source/touch_sen.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DINCLUDE_LOGGING=1 -DINCLUDE_LOG_DEBUG=1 -I"/home/chutao/ECEN_5813/cu-ecen-5813-projects/project_5/project_5/board" -I"/home/chutao/ECEN_5813/cu-ecen-5813-projects/project_5/project_5/source" -I"/home/chutao/ECEN_5813/cu-ecen-5813-projects/project_5/project_5" -I"/home/chutao/ECEN_5813/cu-ecen-5813-projects/project_5/project_5/drivers" -I"/home/chutao/ECEN_5813/cu-ecen-5813-projects/project_5/project_5/CMSIS" -I"/home/chutao/ECEN_5813/cu-ecen-5813-projects/project_5/project_5/utilities" -I"/home/chutao/ECEN_5813/cu-ecen-5813-projects/project_5/project_5/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


