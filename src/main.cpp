#include <Arduino.h>

#include "ModuleConfig.hpp"
#include "ModuleApplication.hpp"
#include "ModuleApplicationBuilder.hpp"

ModuleApplication gApplication;

void setup()
{
#ifdef USE_SERIAL
  Serial.begin(9600);
  Serial.print(F("Starting module, compiled time and date is: "));
  Serial.print(F(__DATE__));
  Serial.println(F(__TIME__));
  Serial.println(F("Enter any char to open the menu..."));
#endif

  ModuleApplicationBuilder gApplicationBuilder;
  gApplicationBuilder.buildApplication(gApplication);
}

void loop()
{
  gApplication.runThreads();
}
