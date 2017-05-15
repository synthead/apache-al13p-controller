#ifndef SETTINGS_H
#define SETTINGS_H

namespace Settings {
  struct settings_struct {
    bool use_celcius;
    int desired_temp;
  };

  extern settings_struct settings;

  bool settings_checksum_valid();
  void write_checksum();
  void set_default_settings();
  void read_settings();
  void write_settings();
  void read_or_set_default_settings();
}

#endif
