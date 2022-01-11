################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:\Users\DavidS\Sloeber\arduinoPlugin\libraries\MPU6050\0.5.0\src\I2Cdev.cpp \
C:\Users\DavidS\Sloeber\arduinoPlugin\libraries\MPU6050\0.5.0\src\MPU6050.cpp 

LINK_OBJ += \
.\libraries\MPU6050\src\I2Cdev.cpp.o \
.\libraries\MPU6050\src\MPU6050.cpp.o 

CPP_DEPS += \
.\libraries\MPU6050\src\I2Cdev.cpp.d \
.\libraries\MPU6050\src\MPU6050.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\MPU6050\src\I2Cdev.cpp.o: C:\Users\DavidS\Sloeber\arduinoPlugin\libraries\MPU6050\0.5.0\src\I2Cdev.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\DavidS\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Users\DavidS\Sloeber\arduinoPlugin\libraries\MPU6050\0.5.0\src" -I"C:\Users\DavidS\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\cores\arduino" -I"C:\Users\DavidS\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\variants\eightanaloginputs" -I"C:\Users\DavidS\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries\MPU6050\src\MPU6050.cpp.o: C:\Users\DavidS\Sloeber\arduinoPlugin\libraries\MPU6050\0.5.0\src\MPU6050.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\DavidS\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Users\DavidS\Sloeber\arduinoPlugin\libraries\MPU6050\0.5.0\src" -I"C:\Users\DavidS\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\cores\arduino" -I"C:\Users\DavidS\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\variants\eightanaloginputs" -I"C:\Users\DavidS\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.3\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


