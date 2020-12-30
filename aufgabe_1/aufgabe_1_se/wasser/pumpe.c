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

void deactivatePwmOutput(){
    CLEAR_BIT(TCCR0A,WGM00);
    CLEAR_BIT(TCCR0A,COM0A1);
    CLEAR_BIT(TCCR0B,CS01);
}
