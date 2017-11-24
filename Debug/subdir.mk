################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Board.cpp \
../ConsoleDisplay.cpp \
../Display.cpp \
../Game.cpp \
../Player.cpp \
../PlayerAI.cpp \
../PlayerHumanLocal.cpp \
../Rules.cpp \
../main.cpp 

OBJS += \
./Board.o \
./ConsoleDisplay.o \
./Display.o \
./Game.o \
./Player.o \
./PlayerAI.o \
./PlayerHumanLocal.o \
./Rules.o \
./main.o 

CPP_DEPS += \
./Board.d \
./ConsoleDisplay.d \
./Display.d \
./Game.d \
./Player.d \
./PlayerAI.d \
./PlayerHumanLocal.d \
./Rules.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/c++/5 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


