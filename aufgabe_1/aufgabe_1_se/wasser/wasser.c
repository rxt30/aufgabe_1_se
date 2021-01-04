#include "pumpe.h"

volatile uint8_t currentWaterValue;

void main(){
    currentWaterValue = 255;
    pwmInputInit(false);
    pwmOutputInit(4999,64);
    outputInit(1);
    timerInit(false,0x00,256);
    while(1){
        if(currentWaterValue < 120){
            turnPumpOn(currentWaterValue);
        }else if(currentWaterValue > 150){
            turnPumpOff();
        }
    }
}

ISR (TIMER0_COMPA_vect){
    TOGGLE_BIT(PORTB,PORTB0);
}

ISR (ADC_vect){
    currentWaterValue = ADCH;
}
