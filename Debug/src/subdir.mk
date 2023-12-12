################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Graph.cpp \
../src/GraphSTS.cpp \
../src/MSExp.cpp \
../src/NewExp.cpp \
../src/Parser.cpp \
../src/SemanticSimilarity.cpp \
../src/Test.cpp \
../src/Util.cpp \
../src/WordModel.cpp \
../src/WordNetL.cpp \
../src/distance.cpp 

CPP_DEPS += \
./src/Graph.d \
./src/GraphSTS.d \
./src/MSExp.d \
./src/NewExp.d \
./src/Parser.d \
./src/SemanticSimilarity.d \
./src/Test.d \
./src/Util.d \
./src/WordModel.d \
./src/WordNetL.d \
./src/distance.d 

OBJS += \
./src/Graph.o \
./src/GraphSTS.o \
./src/MSExp.o \
./src/NewExp.o \
./src/Parser.o \
./src/SemanticSimilarity.o \
./src/Test.o \
./src/Util.o \
./src/WordModel.o \
./src/WordNetL.o \
./src/distance.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-mp-5 -std=c++0x -I/opt/local/include/ -I"C:\Users\RitaA\Downloads\word\word\headers" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Graph.d ./src/Graph.o ./src/GraphSTS.d ./src/GraphSTS.o ./src/MSExp.d ./src/MSExp.o ./src/NewExp.d ./src/NewExp.o ./src/Parser.d ./src/Parser.o ./src/SemanticSimilarity.d ./src/SemanticSimilarity.o ./src/Test.d ./src/Test.o ./src/Util.d ./src/Util.o ./src/WordModel.d ./src/WordModel.o ./src/WordNetL.d ./src/WordNetL.o ./src/distance.d ./src/distance.o

.PHONY: clean-src

