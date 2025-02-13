
#include "ModuleApplicationBuilder.hpp"
#include "ModuleConfig.hpp"
#include "ModuleApplicationIf.hpp"
#include "Model/Vobulator.hpp"
#ifdef USE_ESP32
#include "Model/VobulatorByADC.hpp"
#endif
#include "Controler/SerialPortMenu.hpp"

void ModuleApplicationBuilder::buildApplication(ModuleApplicationIf &rApplication)
{
    setupThreads(rApplication);
}

void ModuleApplicationBuilder::setupThreads(ModuleApplicationIf &rApplication)
{
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