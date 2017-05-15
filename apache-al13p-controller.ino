#include "sensor.h"
#include "relays.h"
#include "display.h"
#include "thermostat.h"
#include "settings.h"
#include "inputs.h"
#include "menu.h"

void setup() {
  Sensor::setup();
  Relays::setup();
  Display::setup();
  Inputs::setup();
  Thermostat::setup();

  Settings::read_or_set_default_settings();
  Sensor::update();
}

void loop() {
  Sensor::loop();
  Inputs::loop();
  Thermostat::loop();
  Menu::loop();
}
