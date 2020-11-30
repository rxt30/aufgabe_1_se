#include "../sharedLibs/sharedFunctions.h"
#define CHANGESOUND(PORT,BIT) PORT = BIT
#define TOGGLE_BIT(PORT,BIT) PORT ^= (1 << BIT)

void specificInit(){
    // Set the Timer Mode to CTC
    TCCR0A |= (1 << WGM01);

    // Set the value that you want to count to
    OCR0A = 0x00;

    TIMSK0 |= (1 << OCIE0A);    //Set the ISR COMPA vect

    sei();         //enable interrupts


    TCCR0B |= (1 << CS02);
    // set prescaler to 256 and start the timer
}

void mainloop(){
}

ISR (TIMER0_COMPA_vect){
    TOGGLE_BIT(PORTB,PORTB0);
}

ISR (INT0_vect){
    if(PIND & (1<<2)){
        OCR0A = 0x00;
    }else{
        OCR0A = 0x46;
    }
    CLEAR_BIT(PORTB,PORTB5);
}


ISR (INT1_vect){
    if(PIND & (1<<3)){
        OCR0A = 0x00;
    }else{
        OCR0A = 0xF3;
    }
    SET_BIT(PORTB,PORTB5);
}

int main(){
    init(6,true);
    specificInit();
    while(1){
        mainloop();
    }
}
