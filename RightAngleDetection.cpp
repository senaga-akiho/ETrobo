#include "RightAngleDetection.h"

float angle_Kp = 0.08;        // <1>
int angle_target = 45;        // <2>
int angle_bias = 0;
int line_limit = 6;

float color_Kp = 0.10;        // <1>
// int line_target = 8;
int color_target = 5;        // <2>
int color_bias = 0;

RightAngleDetection::RightAngleDetection():
  leftWheel(PORT_C), rightWheel(PORT_B),
  colorSensor(PORT_2), sonarSensor(PORT_3){
}

void RightAngleDetection::init() {
  init_f("RightAngleDetection");
}

void RightAngleDetection::terminate() {
  //msg_f("Stopped.", 1);
  leftWheel.stop();
  rightWheel.stop();
}
bool RightAngleDetection::getFin() {
  return fin;
}
void RightAngleDetection::setFin(bool set_fin) {
  fin = set_fin;
}

float RightAngleDetection::calc_prop_value() {
  //const float Kp = 0.83;        // <1>
  // const float Kp = 0.05;        // <1>
  // const int target = 30;        // <2>
  // const int bias = 0;

  // float Kp = 0.08;        // <1>
  // int target = 45;        // <2>
  // int bias = 0;

  //int diff = colorSensor.getBrightness()-target; // <3>元のやつ

  int diff = colorSensor.getBrightness(); // <3>書き換え
  float Kp;
  Kp = angle_Kp;
  if(diff < angle_target){
    Kp = angle_Kp + (angle_target-diff)/60;
  }
  diff=diff-angle_target;//ここまで書き換え
  return (Kp * diff + angle_bias);                       // <4>
}

void RightAngleDetection::run() {
  float turn = calc_prop_value(); // <5>
  int pwm_l = pwm + turn;      // <6>
  int pwm_r = pwm - turn;      // <6>
  leftWheel.setPWM(pwm_l);
  rightWheel.setPWM(pwm_r);
}
void RightAngleDetection::detectionRun() {
  //光の強さを取る
  int diff = colorSensor.getBrightness();
  //光の強さの加減を調べる
  if(diff<min_bri){
        min_bri = diff;
        //msg_f(min_bri,5);
  }
  // if(first){
  //   clock.reset();
  //   first = false;
  // }
  //暗さが一定より低かったら
  detectionIf(diff);
  
}

void RightAngleDetection::detectionIf(int diff) {
  //暗い状態に入った瞬間
  if(diff<line_limit){
      msg_f("stop:angle", 1);
      msg_f(diff, 2);
      leftWheel.stop();
      rightWheel.stop();
      fin = false;
    }else{
    //明るかった時
      //時間のリセット
      clock.reset();
      msg_f("normal...", 1);
      msg_f(diff, 2);
      run();
  }
}
void RightAngleDetection::colorDetection() {
  int diff = colorSensor.getBrightness(); // <3>書き換え
  colorid_t id = colorSensor.getColorNumber();
  msg_f(id,5);
  //暗い状態に入った瞬間
  if((id==0 || id==1 || id==6 || id==7) || clock.now()<2000){
    int pwm_l;      // <6>
    int pwm_r;

    float Kp = color_Kp;
    diff=diff-color_target;//ここまで書き換え
    float turn = Kp * diff + color_bias; 
    
    pwm_l = pwm + turn-5;      // <6>
    pwm_r = pwm - turn-5;
    leftWheel.setPWM(pwm_l);
    rightWheel.setPWM(pwm_r);
  }else{
    leftWheel.stop();
    rightWheel.stop();
    //first = true;
    fin = false;
  }
}
void RightAngleDetection::sonarDetection() {
  int16_t distance = sonarSensor.getDistance(); // <3>書き換え
  msg_f(distance,5);
  //暗い状態に入った瞬間
  if(150>distance){
    clock.sleep(4000);
    leftWheel.setPWM(pwm-1);
    rightWheel.setPWM(pwm);
    int32_t first_count_r;
    first_count_r = rightWheel.getCount();
    while(rightWheel.getCount()-first_count_r < 600){
    }
    leftWheel.stop();
    rightWheel.stop();
    fin = false;
  }
}

