#include "menu.h"
#include "display.h"
#include "sensor.h"
#include <Arduino.h>

namespace Menu {
  void temps() {
    Display::print_temp(0, Sensor::temp);
    Display::print_raw(1, Sensor::raw);
  }
}
