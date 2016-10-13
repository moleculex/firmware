################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/T6819.c \
../src/_74HC595.c \
../src/app.c \
../src/display.c \
../src/flash.c \
../src/function.c \
../src/input.c \
../src/ir.c \
../src/led.c \
../src/main.c \
../src/motorDrive.c \
../src/output.c \
../src/proxySwitch.c \
../src/rotarySwitch.c \
../src/trigger.c \
../src/vcp.c 

OBJS += \
./src/T6819.o \
./src/_74HC595.o \
./src/app.o \
./src/display.o \
./src/flash.o \
./src/function.o \
./src/input.o \
./src/ir.o \
./src/led.o \
./src/main.o \
./src/motorDrive.o \
./src/output.o \
./src/proxySwitch.o \
./src/rotarySwitch.o \
./src/trigger.o \
./src/vcp.o 

C_DEPS += \
./src/T6819.d \
./src/_74HC595.d \
./src/app.d \
./src/display.d \
./src/flash.d \
./src/function.d \
./src/input.d \
./src/ir.d \
./src/led.d \
./src/main.d \
./src/motorDrive.d \
./src/output.d \
./src/proxySwitch.d \
./src/rotarySwitch.d \
./src/trigger.d \
./src/vcp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F30X -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"/Users/peterbruce/Documents/workspace/PLC24/inc/usb" -I"/Users/peterbruce/Documents/workspace/PLC24/system/inc/stm32f3-stdperiph" -I"/Users/peterbruce/Documents/workspace/PLC24/inc/FreeRTOS" -I"/Users/peterbruce/Documents/workspace/PLC24/inc" -I"/Users/peterbruce/Documents/workspace/PLC24/system/inc/cmsis" -I"/Users/peterbruce/Documents/workspace/PLC24/system/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


