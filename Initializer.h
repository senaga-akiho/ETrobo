#include "ev3api.h"
#include "Motor.h"
#include "Clock.h"
#include "util.h"

using namespace ev3api;

using ev3api::Motor;

class Initializer {
  public:
  	explicit Initializer(ev3api::Motor& arm);
	void init();
  private:
  	Motor& m_arm;
  	Clock clock;
  	bool first = true;
};
