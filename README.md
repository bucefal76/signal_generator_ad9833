# signal_generator_ad9833


# Introduction

This is a signal generator for Arduino UNO / ESP32 with use of AD9833 chips.
it uses AD9833 chips. It depends on robtillaart/AD9833 library to talk to the AD9833.
But the idea is the core of functionality can be switch to the different chip without lot of changes.
At least as long as suitable library to talk ith the chip are available.

# Current features

- Single channel sine, square and ramp signal up to 12Mhz.
- Control over serial port.

# Required hardware

- Atmega 328p with Arduino UNO (or clone) + 2 x AD9833 (for two channel configuration).
- ESP32 with Wemos D1 R32 (or clone) + 2 x AD9833 (for two channel configuration).

# Serial port settings

 - COMM port - same as used with Arduino IDE or VSC Platform IO
 - 9600, data bits 8, Stop bits 1, Parity None, XON/XOFF, best to use Putty

# Pinout

## Arduino UNO


      -----------------                                       ----------------
      |               |                                       |              |
      |  ARDUINO      |  Pin 10 ----------------- Pin FSYNCH  |   AD9833     |  Pin Out
      |  UNO          |  Pin 11 ----------------- Pin SDATA   |   Channel 1  |  Pin AGDN
      |               |  Pin 13 ----------------- Pin SCKL    |              | 
      |               |  Pin 5V ----------------- Pin VCC     |              |
      |               |  Pin GND ---------------- Pin DGND    |              |
      -----------------                                       ----------------

## ESP 32

      -----------------                                        ----------------
      |               |                                       |              |
      |  ESP32        |  Pin 12 ----------------- Pin FSYNCH  |   AD9833     |  Pin Out
      |  WEMOS        |  Pin 23 ----------------- Pin SDATA   |   Channel 1  |  Pin AGDN
      |  D1 R32       |  Pin 18 ----------------- Pin SCKL    |              |
      |               |  Pin 3.3V --------------- Pin VCC     |              |
      |               |  Pin GND ---------------- Pin DGND    |              |
      -----------------                                       ----------------

# Architecture

There is "dirty set up code" the application area; see ModuleApplicationBuilder.cpp.
This code is responsible for creating and connecting all building blocks.
The building blocks interact with the echoer through formal interfaces.

The Controller, objects in this area implements ControllerIf - this part of code is responsible for controlling the generators objects.
The Model, objects in this implements the GeneratorIf, this part of code is responsible for talking to the real generator hardware.
Obviously, the View is missing, looks like I entangled data presentation with controller, something to fix in the future :).

# Future developments

 - Dual channel support for Arduino UNO.
 - Dual channel support for ESP32.
 - Use hardware SPI for ESP32 instead of software emulation.
 - Vobulator feature for ESP32.
 - Vobulator feature for UNO.
 - WiFi/Web based UI for ESP32.