#include "../sharedLibs/sharedFunctions.h"
/*
 * OCR1A = 97 = engine on 0°
 * OCR1A = 535 = engine on 180°
 */
ISR (INT0_vect){
	OCR1A = 97;
}
ISR (INT1_vect){
	OCR1A = 535;
}

void main(){
    interruptInit();
	pwmOutputInit(4999,64);
	while (1){
	}
}
