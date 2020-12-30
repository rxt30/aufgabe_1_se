#include "pumpe.h"

void turnPumpOn(int currentWaterValue){
    SET_BIT(PORTB,PORTB1);
    if(currentWaterValue < 80) OCR0A = 0x36;
    else OCR0A = 0x00;
}

void turnPumpOff(){
    CLEAR_BIT(PORTB,PORTB1);
    OCR0A = 0x00;
}
