#include "sensor.h"
#include "relays.h"
#include "display.h"
#include "thermostat.h"
#include "settings.h"

void setup() {
  Sensor::setup();
  Relays::setup();
  Display::setup();

  Settings::read_or_set_default_settings();
}

void loop() {
  Sensor::update();
  float temp = Sensor::get_temp();
  int raw = Sensor::get_raw();

  Display::print_temp(0, temp);
  Display::print_raw(1, raw);

  Thermostat::update(temp);

  delay(500);
}
