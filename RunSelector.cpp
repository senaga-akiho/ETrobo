#include "RunSelector.h"

int color_times = 1;
int b_turne_times = 1;
int s_turne_times = 1;
int angle_times = 1;
RunSelector::RunSelector():mState(SONAR_DETECTION){
}
void RunSelector::terminate() {
  right_angle_detection.terminate();
  move_turne.terminate();
}
void RunSelector::runSelect() {
	switch (mState) {
    case ANGLE_DETECTION:
        msg_f("angleD.", 3);
        angleDetection();
        break;
    case SMALL_TURNE:
        msg_f("smallT.", 3);
        smallTurne();
        break;
    case COLOR_DETECTION:
        msg_f("colorD.", 3);
        colorDetection();
        break;
    case BIG_TURNE:
        //execScenarioTracing();
        msg_f("bigT.", 3);
        bigTurne();
        break;
    case SONAR_DETECTION:
        //execScenarioTracing();
        msg_f("sonarD.", 3);
        sonarDetection();
        break;
    case AAA:
        //execScenarioTracing();
        msg_f("finish.", 3);
        break;
    default:
        break;
    }
}
void RunSelector::angleDetection() {
	right_angle_detection.detectionRun();
	if(right_angle_detection.getFin() == false){
         if(angle_times==1){
            mState = SMALL_TURNE;
        }else if(angle_times==2){
            mState = SMALL_TURNE;
        }else if(angle_times==3){
            mState = SMALL_TURNE;
        }
        angle_times=angle_times+1;
		right_angle_detection.setFin(true);
	}
}
void RunSelector::smallTurne() {
	move_turne.smallTurne();
	if(move_turne.getFin() == false){
        if(s_turne_times==1){
            mState = COLOR_DETECTION;
            // mState = ANGLE_DETECTION;
        }else if(s_turne_times==2){
            mState = ANGLE_DETECTION;
            // mState = COLOR_DETECTION;
        }
        s_turne_times = s_turne_times+1;
		move_turne.setFin(true);
	}
}
void RunSelector::colorDetection() {
    right_angle_detection.colorDetection();
    if(right_angle_detection.getFin() == false){
        if(color_times==1){
            mState = BIG_TURNE;
            // mState = AAA;
        }
        color_times=color_times+1;
        right_angle_detection.setFin(true);
    }
}
void RunSelector::bigTurne() {
    move_turne.bigTurne();
    if(move_turne.getFin() == false){
        if(b_turne_times==1){
            mState = COLOR_DETECTION;
            //mState = AAA;
        }else if(b_turne_times==2){
            mState = ANGLE_DETECTION;
        }
        b_turne_times = b_turne_times+1;
        move_turne.setFin(true);
    }
}
void RunSelector::sonarDetection() {
    right_angle_detection.sonarDetection();
    if(right_angle_detection.getFin() == false){
        // if(b_turne_times==1){
        //     mState = COLOR_DETECTION;
        //     //mState = AAA;
        // }else if(b_turne_times==2){
        //     mState = ANGLE_DETECTION;
        // }
        // b_turne_times = b_turne_times+1;
        right_angle_detection.setFin(true);
        mState = ANGLE_DETECTION;
    }
}