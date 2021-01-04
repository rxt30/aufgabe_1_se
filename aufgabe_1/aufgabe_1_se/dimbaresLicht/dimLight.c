#include "../sharedLibs/sharedFunctions.h"

volatile uint8_t ADCvalue;
volatile uint8_t oldValue;

void main(){
    pwmInputInit(false);
    pwmOutputInit(255,256);
    while(1){
        if(ADCvalue != oldValue){
            OCR1A = ADCvalue;
            oldValue = ADCvalue;
        }
    }
}

ISR(ADC_vect){
    ADCvalue = ADCH;
}
