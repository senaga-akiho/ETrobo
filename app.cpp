#include "app.h"
#include "WheelCtrl.h"
#include "Initializer.h"

#include "util.h"
#include "Clock.h"
// #include "RightAngleDetection.h"//追加
#include "RunSelector.h"//追加


using namespace ev3api;

Motor   gArm(PORT_A);

static Initializer *gInitializer;
//RightAngleDetection right_angle_detection;//追加
RunSelector run_selector;
Clock clock;
WheelCtrl wc;

void main_task(intptr_t unused){
  /*
  SonarSensor sonarSensor(PORT_2);
  センサーのコンストラクタ
  コンストラクタ(関数)
　  ∟オブジェクトを作る際に内容を初期化する関数
  */

  gInitializer = new Initializer(gArm);
  // gInitializer->init();
  init_f(__FILE__);
  while(1){//無限ループ
    msg_f("rooping.", 1);
    run_selector.runSelect(); 
    //左ボタン押下でループ抜ける
    if (ev3_button_is_pressed(LEFT_BUTTON)) {
      run_selector.terminate();
      break;
    }
  }

  ext_tsk();
}

