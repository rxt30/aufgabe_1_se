#include "../sharedLibs/sharedFunctions.h"
#include <stdlib.h>				// needed for itoa function

volatile uint16_t ADCvalue[2] = {0};
volatile uint16_t ADCvalueBefore[2] = {0};
volatile uint16_t ADCvalueNow;


void printSerial(int poti){
	char bufferValue[5];
	char bufferPoti[5];
	if(ADCvalueBefore[poti] != ADCvalue[poti]){
		ADCvalueBefore[poti] = ADCvalue[poti];
		itoa(ADCvalue[poti],bufferValue,10);
		itoa(poti,bufferPoti,10);
		sendString("Poti ");
		sendString(bufferPoti);
		sendString(": ");
		sendString(bufferValue);
		sendString("\r\n");
	}
}


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
		printSerial(0);
		printSerial(1);
	}
}


ISR(ADC_vect) {
	uint8_t tmp;            // temp register for storage of misc data

	tmp = ADMUX;            // read the value of ADMUX register
	tmp &= 0x0F;            // AND the first 4 bits (value of ADC pin being used)

	ADCvalueNow = ADCH;     // read the sensor value

	if (tmp == 0){
		ADCvalue[0] = ADCvalueNow;
		ADMUX++;            // add 1 to ADMUX to go to the next sensor
	}else if (tmp == 1){
		ADCvalue[1] = ADCvalueNow;
		ADMUX &= 0xF8;      // clear the last 4 bits to reset the mux to ADC0
	}
}