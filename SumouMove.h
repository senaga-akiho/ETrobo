#include "WheelCtrl.h"

using namespace ev3api;

class SumouMove{
public:
	void run(int flag);
	bool getFin();
  	void setFin(bool set_fin);
    
private:
    WheelCtrl wc;

    int32_t startRight = 0;
    int32_t startLeft = 0;
    float startAve = 0;

    int32_t nowRight = 0;
    int32_t nowLeft = 0;
    float nowAve = 0;

    float goal = 0;
    bool fin = true;

};