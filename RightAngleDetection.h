#include "Motor.h"
#include "ColorSensor.h"
#include "Clock.h"
#include "util.h"
#include "SonarSensor.h"

using namespace ev3api;

class RightAngleDetection {
public:
  RightAngleDetection();
  void run();
  void detectionRun();
  void detectionIf(int diff);
  void colorDetection();
  void init();
  void terminate();
  float calc_prop_value();
  bool getFin();
  void setFin(bool set_fin);
 private:
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor;
  SonarSensor sonarSensor
  Clock       clock;
  uint32_t max_time = 0;
  int8_t min_bri = 100;
  const int8_t mThreshold = 20;
  const int8_t pwm = (Motor::PWM_MAX) / 10;
  bool first = true;
  bool move = true;
  bool fin = true;
  // const int8_t pwm = (Motor::PWM_MAX) / 6;
 };
