#include "RightAngleDetection.h"

RightAngleDetection::RightAngleDetection():
  leftWheel(PORT_C), rightWheel(PORT_B),
  colorSensor(PORT_2), sonarSensor(PORT_3),
  arm(PORT_A){
}

void RightAngleDetection::init() {
  init_f("RightAngleDetection");
}

void RightAngleDetection::terminate() {
  leftWheel.stop();
  rightWheel.stop();
}
/*終了条件を返すメソッド*/
bool RightAngleDetection::getFin() {
  return fin;
}
void RightAngleDetection::setFin(bool set_fin) {
  fin = set_fin;
}
/*色を返す*/
colorid_t RightAngleDetection::getBcolor() {
    return block_color;
}
colorid_t RightAngleDetection::getFcolor() {
    return floor_color;
}
/*ライントレースの計算*/
float RightAngleDetection::calc_prop_value() {
  int diff = colorSensor.getBrightness(); // <3>書き換え
  float Kp;
  Kp = 0;
  Kp = angle_Kp;
  if(diff < angle_target){
    Kp = angle_Kp + (angle_target-diff)/60;
  }
  diff=diff-angle_target;//ここまで書き換え
  return (Kp * diff + angle_bias);                       // <4>
}
/*走る*/
void RightAngleDetection::run(int set_pwm) {
  float turn = calc_prop_value(); // <5>
  int pwm_l = set_pwm + turn;      // <6>
  int pwm_r = set_pwm - turn;      // <6>
  leftWheel.setPWM(pwm_l);
  rightWheel.setPWM(pwm_r);
}
/*色を返す*/
void RightAngleDetection::detectionRun() {
  //光の強さを取る
  int diff = colorSensor.getBrightness();
  //光の強さの加減を調べる
  if(diff<min_bri){
        min_bri = diff;
  }
  detectionIf(diff);
  
}

void RightAngleDetection::detectionIf(int diff) {
  //暗い状態に入った瞬間
  if(diff<line_limit){
      int back_count = rightWheel.getCount();
      rightWheel.setPWM(-15);
      leftWheel.setPWM(-15);
      while(back_count-rightWheel.getCount() < 10 ){
      }
      leftWheel.stop();
      rightWheel.stop();
      fin = false;
    }else{
      clock.reset();
      run(pwm);
  }
}
/*床の色を検知したら保存*/
void RightAngleDetection::colorDetection() {
  int diff = colorSensor.getBrightness(); // <3>書き換え
  floor_color = colorSensor.getColorNumber();
  if((floor_color==0 || floor_color==1 || floor_color==6 || floor_color==7)){
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
    clock.reset();
    leftWheel.setPWM(-20);
    rightWheel.setPWM(-20);
    while(clock.now()<300){}
    leftWheel.stop();
    rightWheel.stop();
    //first = true;
    fin = false;
  }
}
/*超音波検知して，四秒まってスタート*/
void RightAngleDetection::sonarDetection() {
  int16_t distance = sonarSensor.getDistance(); // <3>書き換え
  msg_f(distance,5);
  //暗い状態に入った瞬間
  if(distance<20 && distance!=0){
    clock.reset();
    //
    while(clock.now()<2500){
      //run(pwm/2);
      int diff = colorSensor.getBrightness(); // <3>書き換え
      int pwm_l;      // <6>
      int pwm_r;

      float Kp = color_Kp;
      diff=diff-color_target;//ここまで書き換え
      float turn = Kp * diff + color_bias; 
      
      pwm_l = pwm + turn-5;      // <6>
      pwm_r = pwm - turn-5;
      leftWheel.setPWM(pwm_l);
      rightWheel.setPWM(pwm_r);
    }
    leftWheel.stop();
    rightWheel.stop();
    // 
    armUp();
    clock.sleep(1000);
    leftWheel.setPWM(50-1);
    rightWheel.setPWM(50);
    int32_t first_count_r;
    first_count_r = rightWheel.getCount();
    while(rightWheel.getCount()-first_count_r < 520){
    }
    leftWheel.stop();
    rightWheel.stop();
    armDown();
    fin = false;
  }
}
void RightAngleDetection::armUp() {
  armMove(40);
}
void RightAngleDetection::armDown() {
  armMove(-40);
}
void RightAngleDetection::armMove(int power) {
  int32_t first_count_a;
  first_count_a = arm.getCount();
  while(true){
    if(power<0){
      arm.setPWM(-5);
      if(arm.getCount()-first_count_a<power){
      arm.reset();
      arm.setPWM(0);
        break;
      }
    }else{
      arm.setPWM(5);
      if(arm.getCount()-first_count_a>power){
        arm.reset();
        arm.setPWM(0);
          break;
      }
    }
  }
}
/*ライン復帰*/
void RightAngleDetection::lineFind(int time) {
  // fin = false;
  int diff = colorSensor.getBrightness(); // <3>書き換え
  if(lf_first==true){
    clock.reset();
    lf_first = false;
  }
  int pwm_l;      // <6>
  int pwm_r;
  //2秒間はライン復帰
  if(clock.now()<time){
    if(diff > line_target){
      pwm_l = pwm + 9;      // <6>
      pwm_r = 0;
    }else{
      pwm_l = 0;      // <6>
      pwm_r = pwm + 9;
    }
    leftWheel.setPWM(pwm_l/1.5);
    rightWheel.setPWM(pwm_r/1.5);
  }else{
    leftWheel.stop();
    rightWheel.stop();
    lf_first = true;
    fin = false;
  }
}
/*ライン復帰*/
void RightAngleDetection::blockColorDetection() {
  int up_num = 1;
  armMove(60);
    while(true){
      armMove(1);
      block_color = colorSensor.getColorNumber();
      if(block_color!=0&&block_color!=1&&block_color!=6&&block_color!=7){
          break;
      }
      up_num = up_num+1;
    }
    armMove(-1*up_num-60);
    fin = false;
}

