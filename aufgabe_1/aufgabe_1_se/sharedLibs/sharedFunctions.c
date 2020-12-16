#include "sharedFunctions.h"

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
 * Reacts to each voltage change.*/
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

/*Enables the serial Monitor via USB*/
void serialInit(){
    UBRR0H = (MYUBBR >> 8);
    UBRR0L = MYUBBR;
    int serialArray[] = {RXEN0,TXEN0,RXCIE0,UCSZ01,UCSZ00};
    for(int i = 0;i < ARRAY_SIZE(serialArray);i++){
        (i < 3) ? (SET_BIT(UCSR0B,serialArray[i])) : (SET_BIT(UCSR0C,serialArray[i]));
    }
    sei();
} 

void setPrescaler(int preScaler,volatile uint8_t *port){
    if(preScaler >= 256) SET_BIT(*port,2);
    if(preScaler <= 64) SET_BIT(*port,1);
    int lastBitCalc = preScaler / 64;
    if(lastBitCalc == 1 || lastBitCalc == 16) SET_BIT(*port,0);
    SET_BIT(*port,2);
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

void timerInit(bool highTimer,int ocrValue,int preScaler){
    if(highTimer){
        timer16bit(ocrValue,preScaler);
    }else{
        timer8bit(ocrValue,preScaler);
    }
    sei();
}
