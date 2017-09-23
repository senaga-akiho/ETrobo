#include "app.h"
#include "util.h"
#include "RunSelector.h"//追加


using namespace ev3api;
RunSelector run_selector;

void main_task(intptr_t unused){
  init_f(__FILE__);
  while(1){//無限ループ
    run_selector.runSelect(); 
    //左ボタン押下でループ抜ける
    if (ev3_button_is_pressed(LEFT_BUTTON)) {
      run_selector.terminate();
      break;
    }
  }

  ext_tsk();
}

