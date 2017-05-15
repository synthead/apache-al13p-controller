#include "display.h"
#include "settings.h"
#include <LiquidCrystal.h>

#define DISPLAY_RS 2
#define DISPLAY_E  3
#define DISPLAY_D4 4
#define DISPLAY_D5 5
#define DISPLAY_D6 6
#define DISPLAY_D7 7

namespace Display {
  // TODO: Allow user to switch between C and F.
  LiquidCrystal lcd(
    DISPLAY_RS,
    DISPLAY_E,
    DISPLAY_D4,
    DISPLAY_D5,
    DISPLAY_D6,
    DISPLAY_D7
  );

  void setup() {
    lcd.begin(16, 2);
  }

  void print_temp(int row, float temp) {
    char text[17];

    if (! Settings::settings.use_celcius) {
      temp = temp * (9 / 5) + 32;
    }

    int temp_whole = temp;
    int temp_decimal = (temp - temp_whole) * 10;

    sprintf(
      text,
      "Temp: %d.%d \xdf%s",
      temp_whole,
      temp_decimal,
      Settings::settings.use_celcius ? "C" : "F"
    );

    print_row(row, text);
  }

  void print_raw(int row, int raw) {
    char text[17];

    sprintf(
      text,
      "Sensor: %d",
      raw
    );

    print_row(row, text);
  }

  void print_row(int row, char* text) {
    char line[17];

    sprintf(line, "%-16s", text);
    lcd.setCursor(0, row);
    lcd.print(line);
  }
}
