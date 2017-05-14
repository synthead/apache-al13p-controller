#include "sensor.h"
#include "relays.h"
#include "display.h"
#include "thermostat.h"

void setup() {
  Sensor::setup();
  Relays::setup();
  Display::setup();
}

void loop() {
  Sensor::update();
  float temp = Sensor::get_temp();

  Display::print_temp(0, temp);
  Display::print_raw(1, Sensor::get_raw());

  Thermostat::update(temp);

  delay(500);
}
