#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define SET_BIT(PORT,BIT) PORT |= (1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT &= ~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^= (1<<BIT)

#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRB |= 0b00000001 << DDB5;
    DDRB |= 0b00000001 << DDB4;

    while(1){
        PORTB |= 1 << PORTB5;
        PORTB &= ~(1 << PORTB4);
        _delay_ms(1000);
        PORTB &= ~(1 << PORTB5);
        PORTB |= 1 << PORTB4;
        _delay_ms(1000);
    }
    return 0;

}
