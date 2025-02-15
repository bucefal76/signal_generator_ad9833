
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
    generatorChannel1 = new GeneratorForEsp32(CHANNEL_1_SPI_CS, CHANNEL_1_SPI_SDATA, CHANNEL_1_SPI_SCLK);
    generatorChannel2 = new GeneratorForEsp32(CHANNEL_2_SPI_CS, CHANNEL_2_SPI_SDATA, CHANNEL_2_SPI_SCLK);
#else
    generatorChannel1 = new GeneratorForUno(CHANNEL_1_SPI_CS);
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