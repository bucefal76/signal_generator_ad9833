
#include "ModuleApplicationBuilder.hpp"
#include "ModuleConfig.hpp"
#include "ModuleApplicationIf.hpp"
#include "Model/Vobulator.hpp"
#ifdef USE_ESP32
#include "Model/VobulatorByADC.hpp"
#endif
#include "Controler/SerialPortMenu.hpp"
#include "Model/GeneratorIf.hpp"
#ifndef USE_ESP32
#include "Model/GeneratorForUno.hpp"
#endif

void ModuleApplicationBuilder::buildApplication(ModuleApplicationIf &rApplication)
{
    setupThreads(rApplication);
}

void ModuleApplicationBuilder::setupThreads(ModuleApplicationIf &rApplication)
{
    GeneratorIf *generatorLine1 = nullptr;
    GeneratorIf *generatorLine2 = nullptr;
#ifdef USE_ESP32

#else
    generatorLine1 = new GeneratorForUno(CHANNEL_1_SPI_CS);
#endif

#ifdef USE_SERIAL
    rApplication.addThread(SerialPortMenu::getInstance());
    SerialPortMenu::getInstance()->setGeneratorsToControl(generatorLine1, generatorLine2);
    SerialPortMenu::getInstance()->enable();
#endif
    rApplication.addThread(Vobulator::getInstance());

#ifdef USE_ESP32
    rApplication.addThread(VobulatorByADC::getInstance());
    VobulatorByADC::getInstance()->enable();
#endif
}