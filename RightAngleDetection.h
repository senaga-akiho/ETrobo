#include "Motor.h"
#include "ColorSensor.h"
#include "Clock.h"
#include "util.h"
#include "SonarSensor.h"
#include "pidCtrl.h"
#include "pid_control.hpp"
#include "onoff_control.hpp"
#include "move.hpp"
#include "robo_meta_datas.hpp"
#include "hsv_converter.hpp"
#include "color_judge.hpp"
//aaa
using namespace ev3api;

class RightAngleDetection {
public:
  RightAngleDetection();
  void angle_run(int set_pwm,int target);
  //void angle_find_run(int set_pwm,int target);
  void angleDetection(int times);
  void firstBrock();
  void secondBrock();
  void thirdBrock();
  void forceBrock();
  void sonarDetection(int times);
  void armDown();
  void armUp();
  void armMove(int power);
  void init();
  void terminate();
  void lineFind(int time);
  bool getFin();
  void setFin(bool set_fin);
  void setAngeleTargetS(int8_t set_color);
  void setAngeleTargetL(int8_t set_color);
  void setColorTarget(int8_t set_color);
  void itemRun();
 private:
  Motor leftWheel;
  Motor rightWheel;
  Motor arm;
  ColorSensor colorSensor;
  SonarSensor sonarSensor;
  Clock       clock;
  pidCtrl pidctrl;
  OnOffControl* stControl = new OnOffControl(0, 0, 0.3, 0);
  Move move_class;

  bool first = true;
  bool fin = true;
  //ラインファインドの最初の判断
  bool lf_first = true;
  //アームを動かす時の最初の判断
  bool arm_first = true;
  //ソナーを使う時の最初の動作の判断
  bool sonar_first = true;
  //ターゲット
  int angle_target_sonar = 210;
  int angle_target_normal = 300;
  int color_target_first = 130;
  int color_target_second = 110;
  //ソナーの時の速さ
  int angle_speed_s = 6;
  //探索中の速さ
  int angle_speed_l = 10;
  //軌道修正の時のはやさ
  int angle_speed_l_f = 6;
  //色検知の時の速さ
  int color_speed_first = 7;
  int color_speed_second = 12;
  int sumou_pwm = 25;
  int item_pwm = 10;
};
