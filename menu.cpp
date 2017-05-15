#include "menu.h"
#include "display.h"
#include "sensor.h"
#include "thermostat.h"
#include "settings.h"
#include <Arduino.h>

namespace Menu {
  int last_raw;
  bool last_heat_on;
  bool last_autotune_running;
  double last_desired_temp;

  void temps() {
    Display::print_temp();
    Display::print_raw();
    Display::print_symbols();
  }

  void loop() {
    if (
      Sensor::raw != last_raw ||
      Thermostat::heat_on != last_heat_on ||
      Thermostat::autotune_running != last_autotune_running ||
      Settings::settings.desired_temp != last_desired_temp
    ) {
      temps();

      last_raw = Sensor::raw;
      last_heat_on = Thermostat::heat_on;
      last_autotune_running = Thermostat::autotune_running;
      last_desired_temp = Settings::settings.desired_temp;
    }
  }
}
