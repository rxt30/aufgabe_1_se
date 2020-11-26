#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define SET_BIT(PORT,BIT) PORT |= (1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT &= ~(1<<BIT)

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void init(int numberOfOutputs, bool interrupt){
    turnOnOutputs(numberOfOutputs);
    if(interrupt){
        turnOnInterrupts();
    }
}

void turnOnInterrupts(){
    CLEAR_BIT(DDRD,DDD2);
    CLEAR_BIT(DDRD,DDD3);

    int registries[] = {PORTD,EICRA,EIMSK};
    int registryShifts[] = {PORTD2,PORTD3,ISC00,ISC10,INT0,INT1};

    for(int i = 0; i < sizeof(registries) / sizeof(int); i++){
        for(int j = 0; j < 2;j++) {
            SET_BIT(registries[i],registryShifts[(2*i)+j]);
        }
    }

    sei();
}

void turnOnOutputs(int numberOfOutputs){
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
