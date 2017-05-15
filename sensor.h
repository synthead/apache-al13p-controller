#ifndef SENSOR_H
#define SENSOR_H

namespace Sensor {
  extern int raw;
  extern double temp;

  void setup();
  void loop();
  void update();
}

#endif
