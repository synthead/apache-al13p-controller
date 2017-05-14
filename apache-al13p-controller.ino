#include "sensor.h"
#include "relays.h"
#include "display.h"

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

  // TODO: Allow user to set this value.
  // TODO: Read/write this value to/from EEPROM.
  // TODO: Move thermostat logic into its own namespace.
  // TODO: Add PID support.
  if (temp >= 150) {
    Relays::heat(false);
  } else {
    Relays::heat(true);
  }

  delay(500);
}
