# LaserShow on Raspberry Pi Zero

This is the second version of my lasershow project. I was using Arduino before but since I started working with linux and RaspberryPi a lot I wanted to move away from Arduino.

![Screenshot](https://raw.githubusercontent.com/tteskac/rpi-lasershow/master/laserpi.jpg)

### Software
- Written in C++ for Raspberry Pi (all versions should work).
- It uses popular WiringPi lib to control GPIOs.
- It uses [ABE_ADCDACPi](https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries/tree/master/ADCDACPi) c++ library from ABElectronics for controlling digital to analog converter from Rpi.

### Hardware
- Raspberry Pi Zero
- MCP4822 DAC. I created my own board for that but you can use [ADC-DAC Pi Zero](https://pinout.xyz/pinout/adc_dac_pi_zero) as well.
- galvo kit (2 galvos + controller board)
- laser diode (green)

# Instalation
1) Install WiringPi: http://wiringpi.com/download-and-install/
2) Clone this project
3) Run ```make``` to build executable
4) Start with ```./lasershow 0 ilda-files/test.ild``` (0 means delay after every point in microseconds)
5) Have fun!

Btw, to create own ILDA files I like to use [Laserworld Showeditor](https://www.showeditor.com/en/features/showeditor-free.html) which has a free version with limited features (but enough for making ILDA files). It's a bit buggy I know but as soon as you get over it you are just fine :) If you know about good open source / free lasershow editor out there that has ILDA export functionality let me know!
Btw#2, this project currently supports only ILDA type 1, so make sure you export correct version.

## Wiring
The code is using SPI for communication with DAC and one GPIO for laser diode:
```
MOSI:  Header pin 19
SCK:     Header pin 23
CS:       Header pin 26

LASER ON: Header pin 11 (WiringPi pin num 0)

+5V:    Header pin 2
GND:   Header pin 6
```

![Rpi pinout](https://docs.particle.io/assets/images/pi-pinout-diagram-01.png)
