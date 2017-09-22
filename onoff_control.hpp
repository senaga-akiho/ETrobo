/**
 * @file onoff_control.hpp
 * @author Suguru Kouchi
 */
#ifndef ONOFF_CONTROL_HPP
#define ONOFF_CONTROL_HPP

#include "control.hpp"

class OnOffControl : public Control{
public:
    OnOffControl(float target);
    OnOffControl(float target, float a, float b, float c);
    float getControlValue(float value);
    void setCoefficient(float a, float b, float c);
    void setPwm(int pwm);
private:
    float target_ = 0.0;
    int pwm_ = 0;
    float a_ = 0.0;
    float b_ = 0.0;
    float c_ = 100.0;

};

#endif

