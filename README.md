# signal_generator_ad9833

Ver 0.2.9

# Introduction

This is a signal generator for Arduino UNO / ESP32 with use of AD9833 chips.
it uses AD9833 chips. It depends on robtillaart/AD9833 library to talk to the AD9833.
But the idea is the core of functionality can be switch to the different chip without lot of changes.
At least as long as suitable library to talk ith the chip are available.

# Current features

- Double or single channel sine, square and ramp signal up to 12Mhz.
- Wobbulator up to 12Mhz (ESP32 for now).
- Control over serial port (same as power).

# Required hardware

- Atmega 328p with Arduino UNO (or clone) + 2 x AD9833 (for two channel configuration).
- ESP32 with Wemos D1 R32 (or clone) + 2 x AD9833 (for two channel configuration).

# Serial port settings

 - COMM port - same as used with Arduino IDE or VSC Platform IO
 - 9600, data bits 8, Stop bits 1, Parity None, XON/XOFF, best to use Putty

# Pinout

The code has basic connectivity test to check SPI connection to the AD9833 generators.
If connection test fails the build in LED will blink at power up with 1sek cycles.
See the GeneratorAd9833::connectivityTest().

## Atmega 328p Arduino UNO

For channel 1, select is a pin 10, other input pins are the same, power is 5V.

      -----------------                                       ----------------
      |               |                                       |              |
      |  ARDUINO      |  Pin 10 ----------------- Pin FSYNCH  |   AD9833     |  Pin Out
      |  UNO          |  Pin 11 ----------------- Pin SDATA   |   Channel 1  |  Pin AGDN
      |               |  Pin 13 ----------------- Pin SCKL    |              | 
      |               |  Pin 5V ----------------- Pin VCC     |              |
      |               |  Pin GND ---------------- Pin DGND    |              |
      -----------------                                       ----------------

For channel 2, select is a pin 9, other input pins are the same, power is 5V.      

      -----------------                                       ----------------
      |               |                                       |              |
      |  ARDUINO      |  Pin 10 ----------------- Pin FSYNCH  |   AD9833     |  Pin Out
      |  UNO          |  Pin 11 ----------------- Pin SDATA   |   Channel 2  |  Pin AGDN
      |               |  Pin 13 ----------------- Pin SCKL    |              | 
      |               |  Pin 5V ----------------- Pin VCC     |              |
      |               |  Pin GND ---------------- Pin DGND    |              |
      -----------------                                       ----------------      

For wobbulator ramp signal output (external ADC MCP 4725):

      -----------------                                       ----------------
      |               |                                       |              |
      |  ARDUINO      |  Pin A4 ----------------- Pin SDA     |   MCP 4725   |  Pin Out
      |  UNO          |  Pin A5 ----------------- Pin SCL     |              |  Pin Gnd
      |               |                                       |              | 
      |               |  Pin 5V ----------------- Pin VCC     |              |
      |               |  Pin GND ---------------- Pin GND     |              |
      -----------------                                       ----------------     

See for details in the include/ModuleConfig.hpp.

## ESP32 Wemos D1 R32

For channel 1, select is a pin 12, other input pins are the same, power is 3.3V.

      -----------------                                        ----------------
      |               |                                       |              |
      |  ESP32        |  Pin 12 ----------------- Pin FSYNCH  |   AD9833     |  Pin Out
      |  WEMOS        |  Pin 23 ----------------- Pin SDATA   |   Channel 1  |  Pin AGDN
      |  D1 R32       |  Pin 18 ----------------- Pin SCKL    |              |
      |               |  Pin 3.3V --------------- Pin VCC     |              |
      |               |  Pin GND ---------------- Pin DGND    |              |
      -----------------                                       ----------------

For channel 2, select is a pin 13, other input pins are the same, power is 3.3V.

      -----------------                                        ----------------
      |               |                                       |              |
      |  ESP32        |  Pin 13 ----------------- Pin FSYNCH  |   AD9833     |  Pin Out
      |  WEMOS        |  Pin 23 ----------------- Pin SDATA   |   Channel 2  |  Pin AGDN
      |  D1 R32       |  Pin 18 ----------------- Pin SCKL    |              |
      |               |  Pin 3.3V --------------- Pin VCC     |              |
      |               |  Pin GND ---------------- Pin DGND    |              |
      -----------------                                       ----------------

For wobbulator ramp signal output (internal ADC) is PIN 25.


See for details in the include/ModuleConfig.hpp.

# Other remarks

- I have noticed that when both generators work at the same time, and one of them is generating a square wave, 
the second generator may get distortion (spikes) as the power lines are not correctly filtered (assuming powering from the UNO board itself).
For this reason, it is recommended that the power lines to both AD9833 devices be thoroughly filtered.

# Architecture

The application area has "dirty set up code"; see ModuleApplicationBuilder.cpp.
This code is responsible for creating and connecting all building blocks.
The building blocks interact with the echoer through formal interfaces.

The Controller, objects in this area implement ControllerIf - this part of the code controls the generator's and wobbulator objects.
The Model, objects in this implement the GeneratorIf, WobbulatorIf and other objects.
This part of code is responsible for talking to the real generator hardware, performing the wobbulator actions or store settings.
The View, objects in this are implement the ViewIf, this part of code is responsible for displaying information to the operator.

<b>Simplified diagram of the project interfaces and classes relationships:</b>

```mermaid
classDiagram
      

      namespace Controller {    
            class ControllerIf
            class SerialPortMenu
      }

      ControllerIf <|.. SerialPortMenu :implements
      <<inerface>> ControllerIf    

      namespace View {
            class ViewIf
            class SerialPortView
      }

      ViewIf <|.. SerialPortView :implements
      <<inerface>> ViewIf    

      namespace Model {
            class WobbulatorIf
            class GeneratorIf
            class RampSignalIf
            class SettingsIf

            class GeneratorAd9933
            class GeneratorForEsp32
            class GeneratorForUno

            class Wobbulator

            class RampSignalForEsp32
            class RampSignalForUno

            class VolatileSettings
      }

      <<inerface>> ViewIf
      <<inerface>> GeneratorIf
      <<inerface>> RampSignalIf      

      GeneratorIf <|.. GeneratorAd9933 : implements
      GeneratorAd9933 <|-- GeneratorForEsp32 : specializes
      GeneratorAd9933 <|-- GeneratorForUno : specializes

      WobbulatorIf <|.. Wobbulator : implements
      RampSignalIf <|.. RampSignalForEsp32 :implements
      RampSignalIf <|.. RampSignalForUno :implements

      SettingsIf <|.. VolatileSettings :specializes

      Wobbulator o-- RampSignalIf
      Wobbulator o-- SettingsIf 
      GeneratorAd9933 o-- SettingsIf

      SerialPortMenu --> ViewIf : uses
      SerialPortMenu --> GeneratorIf : uses
      SerialPortMenu --> WobbulatorIf : ueses

```
# Dependencies

- [robtillaart/AD9833](https://github.com/RobTillaart/AD9833)
- [ivanseidel/ArduinoThread](https://github.com/ivanseidel/ArduinoThread)
- [SPI](https://github.com/esp8266/Arduino/blob/master/libraries/SPI/SPI.h)

For Arduino UNO only

-  [robtillaart/MCP4725](https://github.com/RobTillaart/MCP4725) 
- [mike-matera/ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)

# Future developments

 - Potentiometer to normalize values of signals for different waveforms.

