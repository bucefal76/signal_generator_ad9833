
#include "ModuleApplicationBuilder.hpp"
#include "ModuleConfig.hpp"
#include "ModuleApplicationIf.hpp"
#include "Model/VolatileSettings.hpp"
#include "Model/Wobbulator.hpp"
#include "Model/Potentiometer.hpp"

#ifdef USE_SERIAL
#include "Controller/SerialPortMenu.hpp"
#include "View/SerialPortView.hpp"
#endif

#ifdef USE_ESP32
#include "Model/GeneratorForEsp32.hpp"
#include "Model/RampSignalForEsp32.hpp"
#else
#include "Model/GeneratorForUno.hpp"
#include "Model/RampSignalForUno.hpp"
#endif

#include <SPI.h>

void ModuleApplicationBuilder::buildApplication(ModuleApplicationIf &rApplication)
{
    setupThreads(rApplication);
}

void ModuleApplicationBuilder::setupThreads(ModuleApplicationIf &rApplication)
{
    WobbulatorIf *wobbulator = nullptr;
    SettingsIf *settings = new VoltileSettings();
    RampSignalIf *rampSignal = nullptr;
    ViewIf *view = nullptr;

    GeneratorIf *generatorChannel1 = nullptr;
#ifdef USE_TWO_GENERATORS_FOR_TWO_CHANNELS
    GeneratorIf *generatorChannel2 = nullptr;
#endif

#ifdef USE_ESP32

#ifdef ESP32_USE_HARDWARE_SPI
    // The ESP32 uses hardware SPI interface now.
    SPIClass *spi = new SPIClass(VSPI);
    if (spi != nullptr)
    {
        spi->begin(ESP32_CHANNEL_1_SPI_SCLK, 19U, ESP32_CHANNEL_1_SPI_SDATA, 5U);
        generatorChannel1 = new GeneratorForEsp32(1, spi, ESP32_CHANNEL_1_SPI_CS);
#ifdef USE_TWO_GENERATORS_FOR_TWO_CHANNELS
        generatorChannel2 = new GeneratorForEsp32(2, spi, ESP32_CHANNEL_2_SPI_CS);
#endif
    }
#else
    // The ESP32 uses software emulated SPI interface
    generatorChannel1 = new GeneratorForEsp32(1, ESP32_CHANNEL_1_SPI_CS, ESP32_CHANNEL_1_SPI_SDATA, ESP32_CHANNEL_1_SPI_SCLK);
#ifdef USE_TWO_GENERATORS_FOR_TWO_CHANNELS
    generatorChannel2 = new GeneratorForEsp32(2, ESP32_CHANNEL_2_SPI_CS, ESP32_CHANNEL_2_SPI_SDATA, ESP32_CHANNEL_2_SPI_SCLK);
#endif

#endif // ESP32_USE_HARDWARE_SPI

#else // UNO:
      // For Uno hardware SPI interface need to be initalized first
    SPI.begin();
    generatorChannel1 = new GeneratorForUno(1, UNO_CHANNEL_1_SPI_CS);
#ifdef USE_TWO_GENERATORS_FOR_TWO_CHANNELS
    generatorChannel2 = new GeneratorForUno(2, UNO_CHANNEL_2_SPI_CS);
#endif

#endif // USE_ESP32

#ifdef USE_X9C103S_POTENTIOMETER_TO_NORMALIZE_WAVEFORMS_AMPLITUDES

#ifdef USE_ESP32
#error "Add support for potentiometer for ESP32 or disable the USE_X9C103S_POTENTIOMETER_TO_NORMALIZE_WAVEFORMS_AMPLITUDES"
#else
    PotentiometerIf *potentiometerChannel1 = new Potentiometer(X9C103S_POTENTIOMETER_INC_PIN, X9C103S_POTENTIOMETER_UD_PIN, X9C103S_POTENTIOMETER_CHANNEL_1_CS_PIN);
    generatorChannel1->setPotentiometer(potentiometerChannel1);
#ifdef USE_TWO_GENERATORS_FOR_TWO_CHANNELS
    PotentiometerIf *potentiometerChannel2 = new Potentiometer(X9C103S_POTENTIOMETER_INC_PIN, X9C103S_POTENTIOMETER_UD_PIN, X9C103S_POTENTIOMETER_CHANNEL_2_CS_PIN);
    generatorChannel2->setPotentiometer(potentiometerChannel2);
#endif

#endif

#endif // USE_X9C103S_POTENTIOMETER_TO_NORMALIZE_WAVEFORMS_AMPLITUDES

#ifdef USE_ESP32
    rampSignal = new RampSignalForEsp32();
#else
    rampSignal = new RampSignalForUno();
#endif // USE_ESP32

    wobbulator = Wobbulator::getInstance();
    rApplication.addThread(Wobbulator::getInstance());
    wobbulator->setRampSignal(rampSignal);
    wobbulator->setSettingsStorage(settings);
    wobbulator->setGenerator(generatorChannel1);
    wobbulator->disable();

#ifdef USE_SERIAL
    view = new SerialPortView();
    rApplication.addThread(SerialPortMenu::getInstance());
    SerialPortMenu::getInstance()->setSettingsStorage(settings);
#ifdef USE_TWO_GENERATORS_FOR_TWO_CHANNELS
    SerialPortMenu::getInstance()->setGeneratorsToControl(generatorChannel1, generatorChannel2);
#else
    SerialPortMenu::getInstance()->setGeneratorsToControl(generatorChannel1, nullptr);
#endif
    SerialPortMenu::getInstance()->setWobbulator(wobbulator);
    SerialPortMenu::getInstance()->setView(view);
    SerialPortMenu::getInstance()->enable();
#endif // USE_SERIAL
}