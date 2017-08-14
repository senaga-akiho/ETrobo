#include "RightAngleDetection.h"
#include "MoveTurne.h"

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
  void armDown();
  void terminate();

 private:
  enum State {
        ANGLE_DETECTION,
        SMALL_TURNE,
        COLOR_DETECTION,
        BIG_TURNE,
        SONAR_DETECTION,
        ARM_DOWN,
        AAA
    
  };
  State mState;
  RightAngleDetection right_angle_detection;//追加
  MoveTurne move_turne;//追加
  // const int8_t pwm = (Motor::PWM_MAX) / 6;
 };
