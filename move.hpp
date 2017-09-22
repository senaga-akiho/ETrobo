/**
 * @file move.hpp
 * @author Suguru Kouchi
 */
#ifndef MOVE_HPP
#define MOVE_HPP

#include <cmath>
#include <Motor.h>
#include <Steering.h>
#include <ColorSensor.h>
#include "control.hpp"
#include "onoff_control.hpp"

class Move {
public:
    Move();
    void rotateTail(int degree, int pwm);
    void raiseArm(int degree, int pwm);
    void stop();

    void goStraight(Control& control, float distance /* mm */, int pwm);
    void goStraight(Control& control, int pwm);
    void spin(Control& control, int degree, int pwm);
    void lineTrace(Control& control, int pwm);
    void oldLineTrace(Control& control, float threshold, int pwm);
    float getMileage() const;

private:
    ev3api::Motor leftWheel_;
    ev3api::Motor rightWheel_;
    ev3api::Steering steering_;
    ev3api::Motor tail_;
    ev3api::Motor arm_;
    ev3api::ColorSensor colorSensor_;
    template <class X , class Y> void plusMinusNormalize(X& value , Y& subValue) const;
    const double ROBOT_TREAD       = M_PI * 126.0; // 右タイヤの中心から左タイヤの中心まで
    const double TIRE_OUT_DIAMETER = 1243.5 / 5;   // 360*5度回した走行距離が1243.5mm
    const double ANGLE_COEFFICIENT = 1.043;        // 角度係数 スピン時の論理値と実測の差を埋める
    void showControlData(int brightness, int controlValue) const;
};

/**
 * valueが負の場合、これを正にしてsubValueの正負を反転させます<br>
 * pwmや距離、角度等を正規化する際に使用します<br>
 * 符号付きの整数型まはた浮動小数型で使うこと。
 *
 * @param value    こいつを正にする
 * @param subValue valueが負ならこいつの符号が逆転する
 */
template <class X, class Y>
void Move::plusMinusNormalize(X& value, Y& subValue) const {
    if (value < 0) {
        value *= -1;
        subValue *= -1;
    }
}

#endif
