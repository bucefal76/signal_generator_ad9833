
#include "ModuleApplicationBuilder.hpp"
#include "ModuleConfig.hpp"
#include "ModuleApplicationIf.hpp"
#include "Controler/SerialPortMenu.hpp"
#include "Model/Vobulator.hpp"
#include "Model/GeneratorIf.hpp"

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
#ifdef USE_ESP32
    generatorChannel1 = new GeneratorForEsp32(CHANNEL_1_SPI_CS);
#else
    generatorChannel1 = new GeneratorForUno(CHANNEL_1_SPI_CS);
#endif

#ifdef USE_SERIAL
    rApplication.addThread(SerialPortMenu::getInstance());
    SerialPortMenu::getInstance()->setGeneratorsToControl(generatorChannel1, generatorChannel2);
    SerialPortMenu::getInstance()->enable();
#endif
    rApplication.addThread(Vobulator::getInstance());

#ifdef USE_ESP32
    rApplication.addThread(VobulatorByADC::getInstance());
    VobulatorByADC::getInstance()->enable();
#endif
}