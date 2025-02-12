#include <Arduino.h>

#include "ModuleConfig.hpp"
#include "ModuleApplication.hpp"

ModuleApplication gApplication;

void setup()
{
#ifdef USE_SERIAL
  Serial.begin(9600);
  Serial.print(F("Starting module, compiled time and date is: "));
  Serial.print(F(__DATE__));
  Serial.println(F(__TIME__));
#endif
}

void loop()
{
  gApplication.runThreads();
}
