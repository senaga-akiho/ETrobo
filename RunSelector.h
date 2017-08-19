#include "RightAngleDetection.h"
#include "MoveTurne.h"
#include "SumouMove.h"
#include "ItemMove.h"

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
  void blockColorDetection();
  void sumouRun();
  void itemRun();
  void itemPlace();

 private:
  enum State {
        ANGLE_DETECTION,
        SMALL_TURNE,
        COLOR_DETECTION,
        BIG_TURNE,
        SONAR_DETECTION,
        LINE_FIND,
        BLOCK_COLOR_DETECTION,
        SUMOU_RUN,
        ITEM_RUN,
        ITEM_PLACE,
        AAA
    
  };
  State mState;
  RightAngleDetection right_angle_detection;//追加
  MoveTurne move_turne;//追加
  SumouMove sumou_move;//追加
  ItemMove item_move;//追加
  // const int8_t pwm = (Motor::PWM_MAX) / 6;
 };
