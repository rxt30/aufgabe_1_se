#include "sharedFunctions.h"

/* Set a specicific number of Ports to outputs
 * Starts with PB0-PB4, then PC0-PC5
 * Arguments:
 * numberOfOutputs = Number of Ports as Output
*/

void outputInit(int numberOfOutputs){    
    int outputsArray[] = {DDB0,DDB1,DDB2,DDB3,DDB4,DDB5,DDC0,DDC1,DDC2,DDC3,DDC4,DDC5}; 
    (numberOfOutputs > 12) ? (numberOfOutputs = 12): (numberOfOutputs = numberOfOutputs);
    for(int i = 0; i < numberOfOutputs;i++){
        if(i < 6){
            SET_BIT(DDRB,outputsArray[i]);
        }else{
            SET_BIT(DDRC,outputsArray[i]);
        }
    }
} 

/*Only Works for Interrupts on DDD2 & DDD3
 * Reacts to each voltage change.
 * Triggers the Interrrupts 'INT0_vect' and 'INT1_vect'
*/
void interruptInit(){
    CLEAR_BIT(DDRD,DDD2);
    CLEAR_BIT(DDRD,DDD3);

    volatile uint8_t *ports[] = {&PORTD,&EICRA,&EIMSK};
    uint8_t outputPorts[] = {PORTD2,PORTD3,ISC00,ISC10,INT0,INT1};
    for(int i = 0; i < 6;i++){
        SET_BIT(*(ports[i/2]),outputPorts[i]);
    }
    sei();
}

/*Enables the serial Monitor via USB
 * BAUD-RATE must be determined in the header
 * Triggers the Interrupt 'SPI_STC_vect*
*/
void serialInit(){
    UBRR0H = (MYUBBR >> 8);
    UBRR0L = MYUBBR;
    int serialArray[] = {RXEN0,TXEN0,RXCIE0,UCSZ01,UCSZ00};
    for(int i = 0;i < ARRAY_SIZE(serialArray);i++){
        (i < 3) ? (SET_BIT(UCSR0B,serialArray[i])) : (SET_BIT(UCSR0C,serialArray[i]));
    }
    sei();
} 

/*------Init functions for Timer-------*/
void setPrescaler(int preScaler,volatile uint8_t *port){
    if(preScaler >= 256) SET_BIT(*port,2);
    if(preScaler <= 64) SET_BIT(*port,1);
    int lastBitCalc = preScaler / 64;
    if(lastBitCalc == 1 || lastBitCalc == 16) SET_BIT(*port,0);
}

void timer16bit(int ocrValue, int preScaler){
    //Set Interrupt and Mode
    SET_BIT(TCCR1B,WGM12);
    SET_BIT(TIMSK1,OCIE1A);
    //Set Timer-Value
    OCR1A = ocrValue;
    //Set Prescaler
    setPrescaler(preScaler,&TCCR1B);
}

void timer8bit(int ocrValue,int preScaler){
    //Set Interrupt and Mode
    SET_BIT(TCCR0A,WGM01);
    SET_BIT(TIMSK0,OCIE0A);
    //Set Timer-Value
    OCR0A = ocrValue;
    //Set Prescaler
    setPrescaler(preScaler,&TCCR0B);
}
/* Activates a timer with the given value and preScaler
 * Triggers the Interrupt 'TIMER0_COMPA_vect' 
 * Arguments:
 * highTimer = 16bit (True) or 8bit
 * ocrValue = Calculated Clock-Time
 * preScaler = preScaler for ocrValue
 */

void timerInit(bool highTimer,int ocrValue,int preScaler){
    if(highTimer){
        timer16bit(ocrValue,preScaler);
    }else{
        timer8bit(ocrValue,preScaler);
    }
    sei();
}
/*--------- END ---------*/
    
/*----------Init Functions For pwm-----------*/
/*
 * Initializes a pwm-Input on PORT ADC7
 * Triggers the Interrupt 'ADC_vect'
 * Arguments:
 * highResolution = 16 bit (True) or 8bit
 */
void pwmInputInit(bool highResolution){
    ADMUX = 7;
    ADCSRB = 0;

    SET_BIT(ADMUX,REFS0);
    if(highResolution){
        CLEAR_BIT(ADMUX,ADLAR);
    }else{
        SET_BIT(ADMUX,ADLAR);
    }
    int presets[] = {ADPS0,ADPS1,ADPS2,ADATE,ADEN,ADIE,ADSC};
    for(int i = 0; i < ARRAY_SIZE(presets);i++){
        SET_BIT(ADCSRA,presets[i]);
    }
    sei();
}
/*
 * Initializes a 16bit pwm-Ouput on PORT OC1A
 * Uses the setPrescaler()-Function from the Timer-Block
 * Arguments:
 * icrValue = Value for TOP-Value
 * preScaler = preScaler-Value
 */

void pwmOutputInit(int icrValue,int preScaler){
    SET_BIT(DDRB,DDB1);
    OCR1A = 0;
    ICR1 = icrValue;

    int presets[] = {COM1A1,COM1B1,WGM11};
    for(int i = 0; i < ARRAY_SIZE(presets);i++){
        SET_BIT(TCCR1A,presets[i]);
    }
    SET_BIT(TCCR1B,WGM13);
    SET_BIT(TCCR1B,WGM12);

    setPrescaler(preScaler,&TCCR1B);
}
