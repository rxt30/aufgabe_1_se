#include "../sharedLibs/sharedFunctions.h"
#include <stdlib.h>				// needed for itoa function

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD -1

volatile uint16_t ADCvalue;
volatile uint16_t ADCvalueBefore0;
volatile uint16_t ADCvalueBefore1;
volatile uint16_t ADCvalue0;
volatile uint16_t ADCvalue1;

int main(void) {
	serialInit();
	
	//pwmInputInit(false);

	ADMUX = 0;                // use ADC0
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX |= (1 << ADLAR);    // Right adjust for 8 bit resolution
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
	
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion


	while (1){
		char buffer[5];
		if(ADCvalueBefore0 != ADCvalue0){
			ADCvalueBefore0 = ADCvalue0;
			itoa(ADCvalue0,buffer,10);
			sendString("Poti 0: ");
			sendString(buffer);
			sendString("\r\n");
		}
		if(ADCvalueBefore1 != ADCvalue1){
			ADCvalueBefore1 = ADCvalue1;
			itoa(ADCvalue1,buffer,10);
			sendString("Poti 1: ");
			sendString(buffer);
			sendString("\r\n");
		}
	}
}


ISR(ADC_vect) {
	uint8_t tmp;            // temp register for storage of misc data

	tmp = ADMUX;            // read the value of ADMUX register
	tmp &= 0x0F;            // AND the first 4 bits (value of ADC pin being used)

	ADCvalue = ADCH;        // read the sensor value

	if (tmp == 0){
		ADCvalue0 = ADCvalue;
		ADMUX++;            // add 1 to ADMUX to go to the next sensor
	}else if (tmp == 1){
		ADCvalue1 = ADCvalue;
		ADMUX &= 0xF8;      // clear the last 4 bits to reset the mux to ADC0
	}
	
	// REMEMBER: once ADCH is read the ADC will update
	
	// if you need the value of ADCH in multiple spots, read it into a register
	// and use the register and not the ADCH
}