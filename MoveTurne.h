#include "Motor.h"
#include "ColorSensor.h"
#include "Clock.h"
#include "util.h"

using namespace ev3api;

class MoveTurne {
public:
  MoveTurne();
  void smallTurne();
  void bigTurne();
  void turne(int8_t pwm_r,int8_t pwm_l,int fin_count);
  void init();
  void terminate();
  bool getFin();
  void setFin(bool set_fin);
 private:
  Motor leftWheel;
  Motor rightWheel;
  Motor arm;
  ColorSensor colorSensor;
  Clock       clock;
  const int8_t mThreshold = 20;
  const int8_t pwm = (Motor::PWM_MAX) / 10;
  bool fin = true;
  bool second = true;
  bool movement = true;
 };
