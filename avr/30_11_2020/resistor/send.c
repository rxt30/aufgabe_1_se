// This code waits for a character and transmits the character back (with interrupts)
 

#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t
#include <stdlib.h>
#include <avr/interrupt.h>



#define F_CPU 16000000UL
#define BAUD 9600 
#define MYUBRR F_CPU/16/BAUD -1

volatile uint16_t ADCvalue;
volatile uint16_t oldValue = 0;
volatile uint8_t ADClowValue;
void send(char letter){
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = letter;
}


void sendString(char* letterBuffer){
    while(*letterBuffer){
        send(*letterBuffer++);
    }
    
}

void serialInit(){
    /*Set baud rate */
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;
    
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0B |= (1 << RXCIE0);                    // Enable reciever interrupt
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp

    sei();                                      // Lets not forget to enable interrupts =P
}

void cPortInit(){
        ADMUX = 0;                // use ADC0
    ADMUX |= (1 << REFS0);    // use AVcc as the reference
    ADMUX &= ~(1 << ADLAR);    // Right adjust for 8 bit resolution

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
    ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
    
    ADCSRB = 0;               // 0 for free running mode

    ADCSRA |= (1 << ADEN);    // Enable the ADC
    ADCSRA |= (1 << ADIE);    // Enable Interrupts 

    ADCSRA |= (1 << ADSC);    // Start the ADC conversion

    sei();    // Thanks N, forgot this the first time =P
}

int main(){
    serialInit();
    cPortInit();
    while(1)
    { 
        if(ADCvalue != oldValue){
            char buffer[10];
            itoa(ADCvalue,buffer,10);
            sendString(buffer);
            send('\n');
            send('\r');
            oldValue = ADCvalue;
        }
    }    
}

ISR(ADC_vect){
    ADClowValue = ADCL;
    ADCvalue = (ADCH << 8) + ADClowValue;
}

