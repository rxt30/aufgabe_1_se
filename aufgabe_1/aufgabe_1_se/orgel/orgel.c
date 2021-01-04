#include "soundChange.h"
volatile int interruptDetected;

ISR (TIMER0_COMPA_vect){
    TOGGLE_BIT(PORTB,PORTB0);
}

ISR (INT0_vect){
    interruptDetected = 1;
    CLEAR_BIT(PORTB,PORTB5);
}


ISR (INT1_vect){
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
