#ifndef INCLUDED_WHEEL_CONT
#define INCLUDED_WHEEL_CONT
#include "WheelCtrl.h"
#endif

#include "Motor.h"
#include "Clock.h"


using namespace ev3api;

class ItemMove{
public:
    ItemMove();
	void run();
	void place();
    bool getFin();
    void setFin(bool set_fin);

    
private:
    WheelCtrl wc;
    Motor arm;
    Clock       clock;

    int32_t startRight = 0;
    int32_t startLeft = 0;
    float startAve = 0;

    int32_t nowRight = 0;
    int32_t nowLeft = 0;
    float nowAve = 0;

    float goal = 0;

    bool fin = true;
};