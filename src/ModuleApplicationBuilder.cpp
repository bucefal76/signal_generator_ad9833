
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
#ifndef USE_ESP32
    GeneratorIf *generatorLine1 = new GeneratorForUno(CHANNEL_1_SPI_CS);
    generatorLine1->enableGenerator(GeneratorIf::TypeRamp, 1000);
#endif

#ifdef USE_SERIAL
    rApplication.addThread(SerialPortMenu::getInstance());
    SerialPortMenu::getInstance()->enable();
#endif
    rApplication.addThread(Vobulator::getInstance());

#ifdef USE_ESP32
    rApplication.addThread(VobulatorByADC::getInstance());
    VobulatorByADC::getInstance()->enable();
#endif
}