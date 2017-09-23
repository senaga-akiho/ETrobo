#include "RunSelector.h"

int color_times = 1;
int angle_times = 1;
int line_times = 1;
int big_t_times = 1;
int sonar_times = 1;
int sumou_times = 0;
RunSelector::RunSelector():mState(/*CALIBRATION*/FIRST_ARM_UP/*ITEM_RUN*//*ANGLE_DETECTION*/){
}
void RunSelector::terminate() {
  right_angle_detection.terminate();
}
void RunSelector::runSelect() {
	switch (mState) {
    case CALIBRATION:
        msg_f("CALIBRATION.", 3);
        calibration_f();
        break;
    case ANGLE_DETECTION:
        msg_f("angleD.", 3);
        angleDetection();
        break;
    case FIRST_BROCK:
        msg_f("FB.", 3);
        firstBrock();
        break;
    case SECOND_BROCK:
        msg_f("FB.", 3);
        secondBrock();
        break;
    case THIRD_BROCK:
        msg_f("FB.", 3);
        thirdBrock();
        break;
    case FORCE_BROCK:
        msg_f("FB.", 3);
        forceBrock();
        break;
    case SONAR_DETECTION:
        msg_f("sonarD.", 3);
        sonarDetection();
        break;
    case ITEM_RUN:
        msg_f("ItemR.", 3);
        itemRun();
        break;
    case FIRST_ARM_UP:
        msg_f("FIRST_ARM_UP.", 3);
        firstArmUp();
        break;
    case AAA:
        msg_f("finish.", 3);
        break;
    default:
        break;
    }
}
void RunSelector::calibration_f() {
    right_angle_detection.setAngeleTargetS(calibration.getColor());
    right_angle_detection.setAngeleTargetL(calibration.getColor());
    right_angle_detection.setColorTarget(calibration.getColor());
    mState=FIRST_ARM_UP;
}
void RunSelector::angleDetection() {
	right_angle_detection.angleDetection(angle_times);
	if(right_angle_detection.getFin() == false){
         if(angle_times==1){
            mState = FIRST_BROCK;
        }else if(angle_times==2){
            mState = THIRD_BROCK;
        }else if(angle_times==3){
            if(sonar_times == 3){
                mState = ITEM_RUN;
            }else{
                mState = SONAR_DETECTION;
            }
        }
        angle_times=angle_times+1;
		right_angle_detection.setFin(true);
	}
}
void RunSelector::firstBrock() {
    right_angle_detection.firstBrock();
    if(right_angle_detection.getFin() == false){
        mState = SECOND_BROCK;
        right_angle_detection.setFin(true);
    }
}
void RunSelector::secondBrock() {
    right_angle_detection.secondBrock();
    if(right_angle_detection.getFin() == false){
        mState = ANGLE_DETECTION;
        right_angle_detection.setFin(true);
    }
}
void RunSelector::thirdBrock() {
    right_angle_detection.thirdBrock();
    if(right_angle_detection.getFin() == false){
        mState = FORCE_BROCK;
        right_angle_detection.setFin(true);
    }
}
void RunSelector::forceBrock() {
    right_angle_detection.forceBrock();
    if(right_angle_detection.getFin() == false){
        mState = ANGLE_DETECTION;
        right_angle_detection.setFin(true);
    }
}
void RunSelector::sonarDetection() {
    right_angle_detection.sonarDetection(sonar_times);
    if(right_angle_detection.getFin() == false){
        right_angle_detection.setFin(true);
        color_times = 1;
        angle_times = 1;
        line_times = 1;
        big_t_times = 1;
        // mState = ARM_DOWN;
        if(sonar_times == 1 || sonar_times == 2){
            mState = ANGLE_DETECTION;
        }else if(sonar_times == 3){
            mState = ITEM_RUN;
        }
        sonar_times = sonar_times+1;
    }
}
void RunSelector::itemRun() {
    right_angle_detection.itemRun();
    if(right_angle_detection.getFin() == false){
        mState=AAA;
        right_angle_detection.setFin(true);
    }
}
void RunSelector::firstArmUp() {
    right_angle_detection.armMove(15);
        mState=SONAR_DETECTION;
}