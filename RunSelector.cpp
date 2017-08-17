#include "RunSelector.h"

int color_times = 1;
int angle_times = 1;
int line_times = 1;
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
        msg_f("bigT.", 3);
        bigTurne();
        break;
    case SONAR_DETECTION:
        msg_f("sonarD.", 3);
        sonarDetection();
        break;
    case LINE_FIND:
        msg_f("armD.", 3);
        lineFind();
        break;
    case AAA:
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
        }else if(angle_times==4){
            mState = SMALL_TURNE;
        }else if(angle_times==5){
            mState = SONAR_DETECTION;
        }
        angle_times=angle_times+1;
		right_angle_detection.setFin(true);
	}
}
void RunSelector::smallTurne() {
	move_turne.smallTurne();
	if(move_turne.getFin() == false){
        mState = LINE_FIND;
		move_turne.setFin(true);
	}
}
void RunSelector::colorDetection() {
    right_angle_detection.colorDetection();
    if(right_angle_detection.getFin() == false){
        if(color_times==1){
            mState = BIG_TURNE;
            // mState = AAA;
        }else if(color_times==2){
            mState = BIG_TURNE;
            // mState = COLOR_DETECTION;
        }else if(color_times==3){
            mState = BIG_TURNE;
            // mState = COLOR_DETECTION;
        }else if(color_times==4){
            mState = BIG_TURNE;
            // mState = COLOR_DETECTION;
        }
        color_times=color_times+1;
        right_angle_detection.setFin(true);
    }
}
void RunSelector::bigTurne() {
    move_turne.bigTurne();
    if(move_turne.getFin() == false){
        mState = LINE_FIND;
        move_turne.setFin(true);
    }
}
void RunSelector::sonarDetection() {
    right_angle_detection.sonarDetection();
    if(right_angle_detection.getFin() == false){
        right_angle_detection.setFin(true);
        color_times = 1;
        angle_times = 1;
        line_times = 1;
        // mState = ARM_DOWN;
        mState = LINE_FIND;
    }
}
void RunSelector::lineFind() {
    right_angle_detection.lineFind();
    if(right_angle_detection.getFin() == false){
        if(line_times==1){
            mState = ANGLE_DETECTION;
        }else if(line_times==2){
            mState = COLOR_DETECTION;
        }else if(line_times==3){
            mState = COLOR_DETECTION;
        }else if(line_times==4){
            mState = ANGLE_DETECTION;
        }else if(line_times==5){
            mState = ANGLE_DETECTION;
        }else if(line_times==6){
            mState = COLOR_DETECTION;
        }else if(line_times==7){
            mState = COLOR_DETECTION;
        }else if(line_times==8){
            mState = ANGLE_DETECTION;
        }else if(line_times==9){
            mState = ANGLE_DETECTION;
        }

        line_times=line_times+1;
        right_angle_detection.setFin(true);
    }
}