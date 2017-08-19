#include "Motor.h"
#include "ColorSensor.h"
#include "Clock.h"
#include "util.h"
#include "SonarSensor.h"

using namespace ev3api;

class RightAngleDetection {
public:
  RightAngleDetection();
  void run(int set_pwm);
  void detectionRun();
  void detectionIf(int diff);
  void colorDetection();
  void sonarDetection();
  void armDown();
  void armUp();
  void armMove(int power);
  void init();
  void terminate();
  void lineFind(int time);
  void blockColorDetection();
  float calc_prop_value();
  bool getFin();
  void setFin(bool set_fin);
  colorid_t getBcolor();
  colorid_t getFcolor();
 private:
  Motor leftWheel;
  Motor rightWheel;
  Motor arm;
  ColorSensor colorSensor;
  SonarSensor sonarSensor;
  Clock       clock;
  uint32_t max_time = 0;
  int8_t min_bri = 100;
  const int8_t mThreshold = 20;
  const int8_t pwm = (Motor::PWM_MAX) / 10;
  bool first = true;
  bool move = true;
  bool fin = true;
  //変動あるパラメーター
  // float angle_Kp = 0.10;        // <1>
  float angle_Kp = 0.45; 
  int angle_target = 30;        // <2>
  int angle_bias = 0;
  int line_limit = 6;

  float color_Kp = 0.45;        // <1>
  int color_target = 9;        // <2>
  int color_bias = 0;
  colorid_t floor_color;

  int line_target = 8;
  bool lf_first = true;

  bool arm_first = true;

  const uint32_t duration = 1000;
  int pam=10;
  colorid_t block_color;//98追加
};
