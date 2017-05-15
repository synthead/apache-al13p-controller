#ifndef SENSOR_H
#define SENSOR_H

namespace Sensor {
  extern int raw;
  extern float temp;

  void setup();
  void loop();
  void update();
}

#endif
