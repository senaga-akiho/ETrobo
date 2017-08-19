#include "RunSelector.h"

int color_times = 1;
int angle_times = 1;
int line_times = 1;
int big_t_times = 1;
int sonar_times = 1;
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
    case BLOCK_COLOR_DETECTION:
        msg_f("BlockD.", 3);
        blockColorDetection();
        break;
    case SUMOU_RUN:
        msg_f("sumouR.", 3);
        sumouRun();
        break;
    case ITEM_RUN:
        msg_f("ItemR.", 3);
        itemRun();
        break;
    case ITEM_PLACE:
        msg_f("ItemP.", 3);
        itemPlace();
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
        mState=BLOCK_COLOR_DETECTION;
        right_angle_detection.setFin(true);
    }
}
void RunSelector::bigTurne() {
    if(big_t_times%2 == 1){
        move_turne.bigTurneR();
    }else{
        move_turne.bigTurneL();
    }
    if(move_turne.getFin() == false){
        mState = LINE_FIND;
        move_turne.setFin(true);
        big_t_times = big_t_times+1;
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
        if(sonar_times == 1 || sonar_times == 2){
            mState = LINE_FIND;
        }else if(sonar_times == 3){
            mState = ITEM_RUN;
        }
        sonar_times = sonar_times+1;
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
void RunSelector::blockColorDetection() {
    right_angle_detection.blockColorDetection();
    if(right_angle_detection.getFin() == false){
        mState=SUMOU_RUN;
        msg_f(right_angle_detection.getFcolor(),4);
        msg_f(right_angle_detection.getBcolor(),5);
        right_angle_detection.setFin(true);
    }
}
void RunSelector::sumouRun() {
    int Fid= right_angle_detection.getFcolor();
    int Bid= right_angle_detection.getBcolor();
    if(Fid==Bid){
        //色が一緒だったら寄り切り
        sumou_move.run(0);
    }else{
        //違かったら押し出し
        sumou_move.run(1);
    }
    if(sumou_move.getFin() == false){
        mState=BIG_TURNE;
        sumou_move.setFin(true);
    }
}
void RunSelector::itemRun() {
    item_move.run();
    if(item_move.getFin() == false){
        mState=ITEM_PLACE;
        item_move.setFin(true);
    }
}
void RunSelector::itemPlace() {
    item_move.place();
    if(item_move.getFin() == false){
        mState=AAA;
        item_move.setFin(true);
    }
}