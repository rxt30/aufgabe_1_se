#include "../sharedLibs/sharedFunctions.h"

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
    outputInit(2);
    interruptInit();
    timerInit(false,0x00,256);
    while(1){
        mainloop();
    }
}
