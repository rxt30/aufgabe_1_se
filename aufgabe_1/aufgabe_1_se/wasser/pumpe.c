#include "pumpe.h"
void notificationSound(int currentWaterValue){
    if(currentWaterValue < 80) OCR0A = 0x36;
    else OCR0A = 0x00;
}

void cycleServoEngine(){
    if(OCR1A == 97) OCR1A = 535;
    else OCR1A = 97;
}

void turnPumpOn(int currentWaterValue){
    SET_BIT(PORTB,PORTB1);
    notificationSound(currentWaterValue);
    cycleServoEngine();
}


void turnPumpOff(){
    CLEAR_BIT(PORTB,PORTB1);
    OCR0A = 0x00;
}
