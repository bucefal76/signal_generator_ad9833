
#include "ModuleApplicationBuilder.hpp"
#include "ModuleConfig.hpp"
#include "ModuleApplicationIf.hpp"
#include "Model/Vobulator.hpp"
#include "Model/GeneratorIf.hpp"
#include "View/ViewIf.hpp"

#ifdef USE_SERIAL
#include "Controler/SerialPortMenu.hpp"
#include "View/SerialPortView.hpp"
#endif

#ifdef USE_ESP32
#include "Model/VobulatorByADC.hpp"
#include "Model/GeneratorForEsp32.hpp"
#else
#include "Model/GeneratorForUno.hpp"
#endif

#include <SPI.h>

void ModuleApplicationBuilder::buildApplication(ModuleApplicationIf &rApplication)
{
    setupThreads(rApplication);
}

void ModuleApplicationBuilder::setupThreads(ModuleApplicationIf &rApplication)
{
    GeneratorIf *generatorChannel1 = nullptr;
    GeneratorIf *generatorChannel2 = nullptr;
    ViewIf *view = nullptr;
#ifdef USE_ESP32

#ifdef ESP32_USE_HARDWARE_SPI
    // The ESP32 uses hardware SPI interface now.
    SPIClass *spi = new SPIClass(VSPI);
    if (spi != nullptr)
    {
        spi->begin(ESP32_CHANNEL_1_SPI_SCLK, 19U, ESP32_CHANNEL_1_SPI_SDATA, 5U);
        generatorChannel1 = new GeneratorForEsp32(spi, ESP32_CHANNEL_1_SPI_CS);
        generatorChannel2 = new GeneratorForEsp32(spi, ESP32_CHANNEL_2_SPI_CS);
    }
#else
    // The ESP32 uses software emulated SPI interface
    generatorChannel1 = new GeneratorForEsp32(ESP32_CHANNEL_1_SPI_CS, ESP32_CHANNEL_1_SPI_SDATA, ESP32_CHANNEL_1_SPI_SCLK);
    generatorChannel2 = new GeneratorForEsp32(ESP32_CHANNEL_2_SPI_CS, ESP32_CHANNEL_2_SPI_SDATA, ESP32_CHANNEL_2_SPI_SCLK);
#endif

#else
    // For Uno hardware SPI interface need to be initalized first
    SPI.begin();
    generatorChannel1 = new GeneratorForUno(UNO_CHANNEL_1_SPI_CS);
    generatorChannel2 = new GeneratorForUno(UNO_CHANNEL_2_SPI_CS);
#endif

#ifdef USE_SERIAL
    view = new SerialPortView();
    rApplication.addThread(SerialPortMenu::getInstance());
    SerialPortMenu::getInstance()->setGeneratorsToControl(generatorChannel1, generatorChannel2);
    SerialPortMenu::getInstance()->setView(view);
    SerialPortMenu::getInstance()->enable();
#endif
    rApplication.addThread(Vobulator::getInstance());

#ifdef USE_ESP32
    rApplication.addThread(VobulatorByADC::getInstance());
    VobulatorByADC::getInstance()->enable();
#endif
}