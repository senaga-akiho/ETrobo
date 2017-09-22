#include "RightAngleDetection.h"
#include "Calibration.h"


using namespace ev3api;

class RunSelector {
public:
  RunSelector();
  void runSelect();
  void angleDetection();
  void smallTurne();
  void bigTurne();
  void colorDetection();
  void sonarDetection();
  void lineFind();
  void terminate();
  void itemRun();
  void firstArmUp();
  void calibration_f();
  void moveCenter();
  void backCenter();
  void firstBrock();
  void secondBrock();
  void thirdBrock();
  void forceBrock();

 private:
  enum State {
        ANGLE_DETECTION,
        SONAR_DETECTION,
        ITEM_RUN,
        FIRST_ARM_UP,
        CALIBRATION,
        MOVE_CENTER,
        BACK_CENTER,
        FIRST_BROCK,
        SECOND_BROCK,
        THIRD_BROCK,
        FORCE_BROCK,
        AAA
    
  };
  State mState;
  RightAngleDetection right_angle_detection;//追加
  Calibration calibration;//追加
  int floar_color[8];
  // const int8_t pwm = (Motor::PWM_MAX) / 6;
 };
