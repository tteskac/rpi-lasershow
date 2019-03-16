# LaserShow - Raspberry Pi Zero

This is the second version of my lasershow project. I was using Arduino before but since I started working with linux and RaspberryPi a lot I wanted to move away from Arduino.

![Screenshot](https://raw.githubusercontent.com/tteskac/rpi-lasershow/master/laserpi.jpg)

### Software
- Written in C++ for Rpi
- used [ABE_ADCDACPi](https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries/tree/master/ADCDACPi) c++ library from ABElectronics for controlling digital to analog converter from Rpi.

### Hardware
- Raspberry Pi Zero
- MCP4822 DAC. I created my own board for that but you can use [ADC-DAC Pi Zero](https://pinout.xyz/pinout/adc_dac_pi_zero) as well.
- galvo kit (2 galvos + controller board)
- laser diode (green)

### Todo
- use [ILDA reader](https://github.com/tteskac/ilda-reader) I created for Arduino
