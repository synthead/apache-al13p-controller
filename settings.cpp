#include "settings.h"
#include <EEPROM.h>

#define SETTINGS_CHECK "AL13P_v1"

#define SETTINGS_DESIRED_TEMP 150.0
#define SETTINGS_USE_CELCIUS true

namespace Settings {
  settings_struct settings;

  bool settings_checksum_valid() {
    char check_byte;

    for (int i = 0; i < sizeof SETTINGS_CHECK - 1; i++) {
      check_byte = EEPROM.read(i);

      if (check_byte != SETTINGS_CHECK[i]) {
        return false;
      }
    }

    return true;
  }

  void write_checksum() {
    for (int i = 0; i < sizeof SETTINGS_CHECK; i++) {
      EEPROM.write(i, SETTINGS_CHECK[i]);
    }
  }

  void set_default_settings() {
    settings.desired_temp = SETTINGS_DESIRED_TEMP;
    settings.use_celcius = SETTINGS_USE_CELCIUS;
  }

  void read_settings() {
    EEPROM.get(sizeof SETTINGS_CHECK, settings);
  }

  void write_settings() {
    EEPROM.put(sizeof SETTINGS_CHECK, settings);
  }

  void read_or_set_default_settings() {
    if (settings_checksum_valid()) {
      read_settings();
    } else {
      set_default_settings();
      write_settings();
      write_checksum();
    }
  }
}
