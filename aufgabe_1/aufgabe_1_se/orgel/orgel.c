#include "soundChange.h"
volatile int interruptDetected;
volatile int portStatus;

ISR (TIMER0_COMPA_vect){
    TOGGLE_BIT(PORTB,PORTB0);
}

ISR (INT0_vect){
    portStatus = PIND & (1<<2);
    interruptDetected = 1;
    CLEAR_BIT(PORTB,PORTB5);
}


ISR (INT1_vect){
    portStatus = PIND & (1<<3);
    interruptDetected = 2;
    SET_BIT(PORTB,PORTB5);
}

int main(){
    outputInit(2);
    interruptInit();
    timerInit(false,0x00,256);
    while(1){
        mainloop();
    }
}
