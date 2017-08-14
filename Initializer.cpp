#include "Initializer.h"
#include "ev3api.h"
#include "Motor.h"
// コンストラクタ
// ここでright,left モータのインスタンス作成
Initializer::Initializer(ev3api::Motor& arm):
  m_arm(arm){
}

// 初期化するものがあればここで
void Initializer::init(){
  // int32_t first_count = m_arm.getCount();
  while(true){
  	if(first){
  		clock.reset();
  		first=false;
  	}
    m_arm.setPWM(-10);
    msg_f("initializ", 3);
    // if(m_arm.getCount()-first_count < -50){
    if(clock.now()>2000){
    	m_arm.reset();
    	m_arm.setPWM(0);
    	msg_f("stop", 3);
      	break;
    }
  }
}
