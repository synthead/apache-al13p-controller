#include "menu.h"
#include "display.h"
#include "sensor.h"
#include "thermostat.h"
#include "settings.h"
#include <Arduino.h>

namespace Menu {
  int old_raw;
  bool old_heat_on;
  bool old_autotune_running;
  double old_desired_temp;

  void temps() {
    Display::print_temp();
    Display::print_raw();
    Display::print_symbols();
  }

  void loop() {
    if (
      Sensor::raw != old_raw ||
      Thermostat::heat_on != old_heat_on ||
      Thermostat::autotune_running != old_autotune_running ||
      Settings::settings.desired_temp != old_desired_temp
    ) {
      temps();

      old_raw = Sensor::raw;
      old_heat_on = Thermostat::heat_on;
      old_autotune_running = Thermostat::autotune_running;
      old_desired_temp = Settings::settings.desired_temp;
    }
  }
}
