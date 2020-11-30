#define SET_BIT(PORT,BIT) PORT|=(1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT&=~(1<<BIT)


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


void init() {

    DDRB |= 0b00000001 << DDB4;
    DDRD &= ~(1 << DDD2) & ~(1 << DDD3);
    PORTD |= (1 << PORTD2) | (1 << PORTD3);
    PORTB |= 1 << PORTB5 ;

    EICRA |= (1 << ISC00) | (1 << ISC10);
    EIMSK |= (1 << INT0) | (1 << INT1);
    
    sei();

}

void mainloop() {
//    if ( ! (PIND & (1 << PIND2)))
//        //PORTB = 0xFF;
//        PORTB |= 1 << PORTB5;
//
//    if ( ! (PIND & (1 << PIND3)))
//        PORTB &= ~(1 << PORTB5);
}

int main() {
    init();
    while(1) {
        mainloop();
    }
}

ISR (INT0_vect){
    PORTB |= 1 << PORTB5;
}

ISR (INT1_vect){
    PORTB &= ~(1 << PORTB5);
}
