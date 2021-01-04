#include "soundChange.h"

#define COMPAREPIND(pin,compareNumber) (pin & (1<<compareNumber))

void changeSound(int soundFrequency){
    if(PIND & (1<<2) && PIND & (1<<3)) OCR0A = 0x00;
    else OCR0A = soundFrequency;
}

void mainloop(){
    if(interruptDetected != 0){
        if(interruptDetected == 1) changeSound(0x46);
        else changeSound(0xF3);
        interruptDetected = 0;
}
}
