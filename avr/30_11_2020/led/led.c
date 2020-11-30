#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(){
    DDRD |= (1 << DDD6);
    DDRB |= (1 << DDB5);

    PORTB |= (1 << PORTB5);

    OCR0A = 0;
    // set PWM for 50% duty cycle


    TCCR0A |= (1 << COM0A1);
    // set none-inverting mode

    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    // set fast PWM Mode

    TCCR0B |= (1 << CS01);
    // set prescaler to 8 and starts PWM


    while (1)
    {
        for(int i = 15; i >= 0; i--){
            OCR0A = i*16;
            _delay_ms(100);
        }
        for(int i = 0; i <= 15; i++){
            OCR0A = i*16;
            _delay_ms(100);
        }
    }
}
