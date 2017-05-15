#include "menu.h"
#include "display.h"
#include "sensor.h"
#include "settings.h"
#include <Arduino.h>

#define MENU_TEMP_UPDATE 300

#define MENU_TEMP 0

namespace Menu {
  int menu = MENU_TEMP;

  int last_desired_temp = -1;
  unsigned long next_update_millis = 0;
  unsigned long current_millis;

  void loop() {
    current_millis = millis();

    if (millis() > next_update_millis) {
      menu_temp();
      next_update_millis = current_millis + MENU_TEMP_UPDATE;
    }
  }

  void update() {
    next_update_millis = 0;
  }

  void menu_temp() {
    Display::print_temp(0, Sensor::temp);
    Display::print_raw(1, Sensor::raw);
  }
}
