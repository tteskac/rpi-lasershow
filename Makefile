# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall (warnings all) turns on most, but not all, compiler warnings
CFLAGS  = -Wall

# the build target executable:
TARGET = lasershow

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp ABE_ADCDACPi.cpp

clean:
	$(RM) $(TARGET)
