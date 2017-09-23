#include "RightAngleDetection.h"


RightAngleDetection::RightAngleDetection():
  leftWheel(PORT_C), rightWheel(PORT_B),
  colorSensor(PORT_3), sonarSensor(PORT_2),
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
void RightAngleDetection::setAngeleTargetS(int8_t set_color) {
  angle_target_sonar = set_color;
}
void RightAngleDetection::setAngeleTargetL(int8_t set_color) {
  angle_target_normal = set_color;
}
void RightAngleDetection::setColorTarget(int8_t set_color) {
  color_target_first = set_color;
}
/*
  直角検知に使う時のライントレース

  @param set_pwm セットするパワー
  @param target 線のRGBのしきい値
*/
void RightAngleDetection::angle_run(int set_pwm,int target) {
  pidctrl.setTargetColor(target);
  float turn = pidctrl.calcColorWalkPid();
  turn *= 0.01;
  int pwm_l = set_pwm * (1.0 + turn);
  int pwm_r = set_pwm * (1.0 - turn);
  leftWheel.setPWM(pwm_l);
  rightWheel.setPWM(pwm_r);
}
/*
  直角検知

  @param times この関数が呼ばれた回数
*/
void RightAngleDetection::angleDetection(int times) {
  arm.setPWM(0);
  // //一回目は通る
  if(first){
    //角度の初期値を取って
    int32_t first_count_r = rightWheel.getCount();
    int32_t first_count_l = leftWheel.getCount();
    int32_t count_r = rightWheel.getCount()-first_count_r;
    int32_t count_l = leftWheel.getCount()-first_count_l;
    //一定進むまでライントレース
    if(times==1){
      while((count_r+count_l)/2 < 200){
        count_r = rightWheel.getCount()-first_count_r;
        count_l = leftWheel.getCount()-first_count_l;
        angle_run(angle_speed_l_f,angle_target_normal);
      }
    }else{
      while((count_r+count_l)/2 < 100){
        count_r = rightWheel.getCount()-first_count_r;
        count_l = leftWheel.getCount()-first_count_l;
        angle_run(angle_speed_l_f,angle_target_normal);
      }
    }
    first=false;
  }
  //光の強さを取る
  int diff = colorSensor.getBrightness();
  //RGBの値を取って，足す
  rgb_raw_t rgb;
  colorSensor.getRawColor(rgb);
  int color_val = rgb.r + rgb.g +rgb.b;
  msg_f(color_val,4);
  // if(diff<line_limit){
  //暗い状態に入った瞬間
  if(color_val<80){
    if(times == 3){
      move_class.goStraight(*stControl,10, 30);
    }
    leftWheel.stop();
    rightWheel.stop();
    fin = false;
    first=true;
  }else{
    //進む
    angle_run(angle_speed_l,angle_target_normal);
  }
}
/*
  １個目のブロックに行く

*/
void RightAngleDetection::firstBrock() {
  move_class.goStraight(*stControl,50, sumou_pwm);
  move_class.spin(*stControl,90,15);
  move_class.goStraight(*stControl,230, sumou_pwm);
  move_class.goStraight(*stControl,120, -sumou_pwm);
  fin=false;
}
/*
  ２個目のブロックに行く
*/
void RightAngleDetection::secondBrock() {
  move_class.spin(*stControl,180, -sumou_pwm);
  move_class.goStraight(*stControl,330, sumou_pwm);
  move_class.goStraight(*stControl,240, -sumou_pwm);
  move_class.spin(*stControl,90, sumou_pwm);//新幹線に当たらないよう変更
  move_class.goStraight(*stControl,80, -sumou_pwm);//新幹線に当たらないよう変更
  move_class.spin(*stControl,180, sumou_pwm);//新幹線に当たらないよう変更
  //move_class.spin(*stControl,90, -sumou_pwm);//本来
  fin=false;
}
/*
  3個目のブロックに行く
*/
void RightAngleDetection::thirdBrock() {
   move_class.goStraight(*stControl,50, sumou_pwm);
  move_class.spin(*stControl,90,15);
  move_class.goStraight(*stControl,230, sumou_pwm);
   move_class.goStraight(*stControl,120, -sumou_pwm);
  fin=false;
}
/*
  4個目のブロックに行く
*/
void RightAngleDetection::forceBrock() {
  move_class.spin(*stControl,180, -sumou_pwm);
  move_class.goStraight(*stControl,330, sumou_pwm);
  move_class.goStraight(*stControl,250, -sumou_pwm);
  move_class.spin(*stControl,90, sumou_pwm);//新幹線に当たらないよう変更
  move_class.goStraight(*stControl,80, -sumou_pwm);//新幹線に当たらないよう変更
  move_class.spin(*stControl,180, sumou_pwm);//新幹線に当たらないよう変更
  // move_class.spin(*stControl,90, -sumou_pwm);//本来
  fin=false;
}

/*

  超音波検知して，1.5秒まってスタート
*/
void RightAngleDetection::sonarDetection(int times) {
  if(sonar_first==true){
    sonar_first=false;
    //ライントレースをして角度を整える
    int32_t first_count;
    first_count = rightWheel.getCount();
    first_count +=leftWheel.getCount();
    int32_t now_count = (rightWheel.getCount()+leftWheel.getCount()-first_count)/2;
    while(now_count < 80){
      now_count = (rightWheel.getCount()+leftWheel.getCount()-first_count)/2;
      angle_run(angle_speed_s,angle_target_sonar);
    }
    leftWheel.stop();
    rightWheel.stop();
  }
  int16_t distance = sonarSensor.getDistance(); // <3>書き換え
  msg_f(distance,4);
  //距離が縮まった瞬間
  if(distance<210 && distance!=0){
    leftWheel.stop();
    rightWheel.stop();
    // 
    clock.sleep(1500);
    armUp();
    if(times==1){
      leftWheel.setPWM(60);
      rightWheel.setPWM(60);
    }else{
      leftWheel.setPWM(35);
      rightWheel.setPWM(36);
    }
    int32_t first_count_r;
    first_count_r = rightWheel.getCount();
    while(rightWheel.getCount()-first_count_r < 550){
    }
    leftWheel.stop();
    rightWheel.stop();
    clock.sleep(500);
    armDown();
    sonar_first=true;
    fin = false;
  }else{
  }
}
//ARMをあげる
void RightAngleDetection::armUp() {
  armMove(20);
}
//ARMを下げる
void RightAngleDetection::armDown() {
  armMove(-20);
}
void RightAngleDetection::armMove(int angle) {
  int32_t first_count_a;
  first_count_a = arm.getCount();
  while(true){
    if(angle<0){
      arm.setPWM(-50);
      if(arm.getCount()-first_count_a<angle){
      arm.reset();
      arm.setPWM(0);
        break;
      }
    }else{
      arm.setPWM(10);
      if(arm.getCount()-first_count_a>angle){
        arm.reset();
        arm.setPWM(0);
          break;
      }
    }
  }
}
/*
  懸賞
*/
void RightAngleDetection::itemRun() {
  armMove(-15);
  move_class.goStraight(*stControl,125, -item_pwm);
  clock.sleep(300);
  move_class.spin(*stControl,90, item_pwm);
  clock.sleep(300);
  move_class.goStraight(*stControl,250, item_pwm);
  armMove(85);
  while(true){
    int16_t distance = sonarSensor.getDistance(); // <3>書き換え
    msg_f(distance,4);
    if(distance<50 && distance!=0){
      break;
    }
  }
  move_class.goStraight(*stControl,420, -item_pwm);
  clock.sleep(300);
  move_class.spin(*stControl,90, -item_pwm);
  clock.sleep(300);
  move_class.goStraight(*stControl,100, item_pwm);
  clock.sleep(300);
  move_class.goStraight(*stControl,475, item_pwm);
  move_class.spin(*stControl,90, item_pwm);
  clock.sleep(300);
  move_class.goStraight(*stControl,240, item_pwm);
  armMove(-70);
  move_class.goStraight(*stControl,55, -item_pwm);
  clock.sleep(300);
  move_class.spin(*stControl,90, -item_pwm);
  fin=false;
}


