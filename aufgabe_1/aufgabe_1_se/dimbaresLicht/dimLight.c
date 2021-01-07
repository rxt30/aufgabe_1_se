#include "../sharedLibs/sharedFunctions.h"

volatile uint8_t ADCvalue;
volatile uint8_t oldValue;

void main(){
    pwmInputInit(false);
    pwmOutputInit(255,256);
    while(1){
    }
}

ISR(ADC_vect){
    OCR1A = ADCH;
}
