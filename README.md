# signal_generator_ad9833


# Introduction
This is a signal generator for Arduino UNO / ESP32 with use of AD9833 chips.
it uses AD9833 chips. It depends on robtillaart/AD9833 library to talk to the AD9833.
But the idea is the core of functionality can be switch to the different chip without lot of changes.
At least as long as suitable library to talk ith the chip are available.

# Current features

- Single channel sine, square and ramp signal up to 12Mhz.
- Control over serial port.

# Serial port settings

 - COMM port - same as used with Arduino IDE or VSC Platform IO
 - 9600, data bits 8, Stop bits 1, Parity None, XON/XOFF, best to use Putty

# Pinouts

## Arduino UNO


        -----------------                                       ----------------
        |               |                                       |              |
        |      UNO      |  Pin 10 ----------------- Pin FSYNCH  |   AD9833     |  Pin Out  ---  your scope
        |               |  Pin 11 ----------------- Pin SDATA   |   Channel 1  |  Pin AGDN --- your scope
        |               |  Pin 13 ----------------- Pin SCKL    |              |
        |               |  Pin 5V ----------------- Pin VCC     |              |
        |               |  Pin GND ---------------- Pin DGND    |              |
        -----------------                                       ----------------

## ESP 32

TO DO

# Future developments

 - Single channel support for ESP32
 - Dual channel support for Arduino UNO
 - Dual channel support for ESP32
 - Vobulator feature for ESP32
 - Vobulator feature for UNO
 - WiFi/Web based UI for ESP32