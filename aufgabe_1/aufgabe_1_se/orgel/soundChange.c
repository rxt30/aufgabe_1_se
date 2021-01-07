#include "soundChange.h"

void changeSound(int soundFrequency){
    OCR0A = soundFrequency;
}

void changeSoundonLastInterrupt(){
    if(interruptDetected == 1) changeSound(0x46);
    else changeSound(0xF3);
}

void mainloop(){
    //Needed to prevent weird soundChanges
    int tmp = portOff1 | portOff2;
    switch(tmp){
        case 0: changeSoundonLastInterrupt();break;
        case 4: changeSound(0xF3);break;
        case 8: changeSound(0x46);break;
        default: changeSound(0x00);
    }
}
