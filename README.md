# LaserShow on Raspberry Pi Zero

This is the second version of my lasershow project. I was using Arduino before but since I started working with linux and RaspberryPi I wanted to move away from Arduino as it is much simpler to write code for me on linux (oh, and of course, multithreading!).

![Screenshot](https://raw.githubusercontent.com/tteskac/rpi-lasershow/master/laserpi.jpg)

### Software
- Written in C++ for Raspberry Pi (all versions should work).
- It uses popular WiringPi lib to control GPIOs.
- It uses [ABE_ADCDACPi](https://github.com/abelectronicsuk/ABElectronics_CPP_Libraries/tree/master/ADCDACPi) c++ library from ABElectronics for controlling digital to analog converter from Rpi.

### Hardware
- Raspberry Pi Zero
- MCP4822 DAC. I created my own board for that but you can use e.g. [ADC-DAC Pi Zero](https://pinout.xyz/pinout/adc_dac_pi_zero) as well.
- galvo kit (2 galvos + controller board)
- laser diode (e.g. green)

# Instalation
1) Install WiringPi: http://wiringpi.com/download-and-install/
2) Clone this project
3) Run ```make``` to build executable
4) Start with ```./lasershow 0 ilda-files/test.ild``` (0 means delay after every point in microseconds)
5) Have fun!

Btw, to create own ILDA files I like to use [Laserworld Showeditor](https://www.showeditor.com/en/features/showeditor-free.html) which has a free version with limited features (but enough for making ILDA files). It's a bit buggy I know but as soon as you get over it you are just fine :) If you know about good open source / free lasershow editor out there that has ILDA export functionality let me know!
Btw#2, this project currently supports only ILDA Format 1 (2D Coordinates with Indexed Color) and Format 5 (2D Coordinates with True Colors), so make sure you export correct version.

## Wiring
The code is using SPI for communication with DAC and one GPIO for laser diode:
```
/-----------------------------------------\
| MCP4822       | RASPBERRY ZERO          |
|-----------------------------------------|
| PIN 1 (Vdd)   | +5V pin, e.g. 2         |
| PIN 2 (CS)    | PIN 26 (CE1)            |
| PIN 3 (SCK)   | PIN 23 (SCK)            |
| PIN 4 (SDI)   | PIN 19 (MOSI)           |
| PIN 5 (LDAC)  | GND pin, e.g. 20        |
| PIN 7 (Vss)   | GND pin, e.g. 6         |
|-----------------------------------------|
| PIN 8 (VoutA) | To galvo X              |
| PIN 6 (VoutB) | To galvo Y              |
| LASER ON      | PIN 11 (WiringPi pin 0) |
\-----------------------------------------/
```

![DAC](https://raw.githubusercontent.com/tteskac/rpi-lasershow/master/mcp48x2.png)

![Rpi pinout](https://docs.particle.io/assets/images/pi-pinout-diagram-01.png)
