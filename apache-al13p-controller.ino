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

  Settings::read_or_set_default_settings();
}

void loop() {
  Sensor::update();

  Inputs::loop();
  Menu::loop();

  Thermostat::update(Sensor::temp);
}
