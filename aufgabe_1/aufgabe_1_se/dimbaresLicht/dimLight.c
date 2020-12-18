#include "../sharedLibs/sharedFunctions.h"

volatile uint8_t ADCvalue;
volatile uint8_t oldValue;

void main(){
    pwmInit(false);
    while(1){
        if(ADCvalue != oldValue){
            OCR0A = ADCvalue;
            oldValue = ADCvalue;
        }
    }
}

ISR(ADC_vect){
    ADCvalue = ADCH;
}
