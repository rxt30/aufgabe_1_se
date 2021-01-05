#include "pumpe.h"
void notificationSound(int currentWaterValue){
    if(currentWaterValue < 80) OCR0A = 0x36;
    else OCR0A = 0x00;
}

void turnPumpOn(int currentWaterValue){
    notificationSound(currentWaterValue);
    OCR1A = 535;
}


void turnPumpOff(){
    OCR0A = 0x00;
    OCR1A = 97;
}
