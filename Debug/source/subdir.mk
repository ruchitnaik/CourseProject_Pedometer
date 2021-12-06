################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Course_Project.c \
../source/i2c.c \
../source/lcd.c \
../source/mma8451.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/timer.c \
../source/utility.c 

OBJS += \
./source/Course_Project.o \
./source/i2c.o \
./source/lcd.o \
./source/mma8451.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/timer.o \
./source/utility.o 

C_DEPS += \
./source/Course_Project.d \
./source/i2c.d \
./source/lcd.d \
./source/mma8451.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/timer.d \
./source/utility.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\rtrru\Documents\MCUXpressoIDE_11.4.1_6260\workspace\Course_Project\board" -I"C:\Users\rtrru\Documents\MCUXpressoIDE_11.4.1_6260\workspace\Course_Project\source" -I"C:\Users\rtrru\Documents\MCUXpressoIDE_11.4.1_6260\workspace\Course_Project" -I"C:\Users\rtrru\Documents\MCUXpressoIDE_11.4.1_6260\workspace\Course_Project\startup" -I"C:\Users\rtrru\Documents\MCUXpressoIDE_11.4.1_6260\workspace\Course_Project\CMSIS" -I"C:\Users\rtrru\Documents\MCUXpressoIDE_11.4.1_6260\workspace\Course_Project\drivers" -I"C:\Users\rtrru\Documents\MCUXpressoIDE_11.4.1_6260\workspace\Course_Project\utilities" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


