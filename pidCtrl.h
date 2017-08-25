#include "ev3api.h"
#include "ColorSensor.h"
#ifndef INCLUDED_WHEEL_CONT
#define INCLUDED_WHEEL_CONT
#include "WheelCtrl.h"
#endif

using ev3api::ColorSensor;

class pidCtrl {

  public:
	pidCtrl();
	float calcPid();
	float calcColorPid();
	float calcColorWalkPid();
	float calcMotorPid();
	void setLineRL(int setRL);
	void setTargetBrightness(int setTarget);
	void setTargetColor(int setTarget);
  private:
	int LineRL;
	ColorSensor colorSensor;
	WheelCtrl wheelCtrl;
	const float delta_t = 0.002;
	const float Kp = 0.63;
	const float Ki = 0.0;
	const float Kd = 0.0;

//	const float Kp_color = 0.12;
	const float Kp_color = 0.04;
//	const float Ki_color = 0.1;
	const float Ki_color = 0.0;
//	const float Kd_color = 0.006;
//	const float Kd_color = 0.003;
	const float Kd_color = 0.000;

//	const float Kp_color_walk = 0.14;
	const float Kp_color_walk = 0.50;
	const float Ki_color_walk = 0.0;
//	const float Kd_color_walk = 0.005;
	const float Kd_color_walk = 0.01;

	int diff[2];
	int diff_color[2];
	int diff_color_walk[2];
	int motor_diff[2];
	float integral;
	float motor_integral;
	unsigned int target_val = 20;
//	unsigned int target_val_color = 360; 本番コースで調整した値
//	unsigned int target_val_color = 280;
	unsigned int target_val_color = 200;//難所用
};

