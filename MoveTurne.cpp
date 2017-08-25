#include "MoveTurne.h"


MoveTurne::MoveTurne():
  leftWheel(PORT_C), rightWheel(PORT_B),
  colorSensor(PORT_2),arm(PORT_A) {
}

void MoveTurne::init() {
  init_f("MoveTurne");
}

void MoveTurne::terminate() {
  leftWheel.stop();
  rightWheel.stop();
}
bool MoveTurne::getFin() {
  return fin;
}
void MoveTurne::setFin(bool set_fin) {
  fin = set_fin;
}
int32_t first_count_r;
int32_t first_count_l;

void MoveTurne::smallTurne() {
  turne(pwm*1,pwm*-1,105);
}
void MoveTurne::bigTurneR() {
  //turne(pwm*-1,pwm*1,-270);
  turne(pwm*-1,pwm*1,-280);
}
void MoveTurne::bigTurneL() {
  int diff = 0;
  diff = colorSensor.getBrightness();
  while(diff>8){
    diff = colorSensor.getBrightness(); // <3>書き換え
    turne(pwm*1,pwm*-1,2);
  }
  turne(pwm*1,pwm*-1,70);
}
void MoveTurne::turne(int8_t pwm_r,int8_t pwm_l,int fin_count) {
  if(movement == true){
    if(second==true){
      first_count_r = rightWheel.getCount();
      first_count_l = leftWheel.getCount();
      second=false;
    }
    rightWheel.setPWM(pwm_r);
    leftWheel.setPWM(pwm_l);
    int32_t moter_diff = rightWheel.getCount()-first_count_r;
    //マイナスだったら裏返す
    if(fin_count < 0){
      fin_count = fin_count*-1;
      moter_diff = moter_diff*-1;
    }
    //回したい角度まで回したら止める
    if (moter_diff > fin_count) {
      movement = false;
      leftWheel.stop();
      rightWheel.stop();
      second = true;
    }
  }else{
     msg_f("LineFind.",3);
    leftWheel.stop();
    rightWheel.stop();
    fin = false;
    movement = true;
  }
}
