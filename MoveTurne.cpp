#include "MoveTurne.h"

int line_target = 8;

MoveTurne::MoveTurne():
  leftWheel(PORT_C), rightWheel(PORT_B),
  colorSensor(PORT_2) {
}

void MoveTurne::init() {
  init_f("MoveTurne");
}

void MoveTurne::terminate() {
  //msg_f("Stopped.", 1);
  leftWheel.stop();
  rightWheel.stop();
}
bool MoveTurne::getFin() {
  return fin;
}
void MoveTurne::setFin(bool set_fin) {
  fin = set_fin;
}
bool first = false;
bool lf_first = false;
bool second = false;
bool movement = false;
int32_t first_count_r;
int32_t first_count_l;
// void MoveTurne::smallTurne() {
//   if(movement == false){
//     if(first==false){
//       first_count_r = rightWheel.getCount();
//       first_count_l = leftWheel.getCount();
//       first=true;
//     }
//     leftWheel.setPWM(-pwm*1);
//     rightWheel.setPWM(pwm*1);
//     int32_t moter_diff = first_count_r-rightWheel.getCount();
//     msg_f(moter_diff,4);
//     if (moter_diff < -95) {
//       movement = true;
//       leftWheel.stop();
//       rightWheel.stop();
//       first = false;
//     }
//   }else{
//     lineFind();
//   }
// }
// void MoveTurne::bigTurne() {
//   if(movement == false){
//     if(second==false){
//       first_count_r = rightWheel.getCount();
//       first_count_l = leftWheel.getCount();
//       second=true;
//     }
//       leftWheel.setPWM(pwm*1);
//       rightWheel.setPWM(-pwm*1);
//       int32_t moter_diff = rightWheel.getCount()-first_count_r;
//       if (moter_diff < -280) {
//         movement = true;
//         leftWheel.stop();
//         rightWheel.stop();
//         second = false;
//       }
//   }else{
//     lineFind();
//   }
// }
void MoveTurne::smallTurne() {
  turne(pwm*1,pwm*-1,95);
}
void MoveTurne::bigTurne() {
  turne(pwm*-1,pwm*1,-280);
}
void MoveTurne::turne(int8_t pwm_r,int8_t pwm_l,int fin_count) {
  if(movement == false){
    if(second==false){
      first_count_r = rightWheel.getCount();
      first_count_l = leftWheel.getCount();
      second=true;
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
      movement = true;
      leftWheel.stop();
      rightWheel.stop();
      second = false;
    }
  }else{
     msg_f("LineFind.", 4);
    lineFind();
  }
}
void MoveTurne::lineFind() {
  int diff = colorSensor.getBrightness(); // <3>書き換え
  if(lf_first==false){
    clock.reset();
    lf_first = true;
  }
  int pwm_l;      // <6>
  int pwm_r;
  if(clock.now()<1500){
    if(diff > line_target){
      pwm_l = pwm + 9;      // <6>
      pwm_r = 0;
    }else{
      pwm_l = 0;      // <6>
      pwm_r = pwm + 9;
    }
    leftWheel.setPWM(pwm_l);
    rightWheel.setPWM(pwm_r);
  }else{
    leftWheel.stop();
    rightWheel.stop();
    lf_first = false;
    fin = false;
    movement = false;
  }
}



