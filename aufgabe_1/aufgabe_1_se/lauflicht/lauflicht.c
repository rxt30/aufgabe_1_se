#include "../sharedLibs/sharedFunctions.h"
#include "segmentFunction.h"
#include <util/delay.h>


int mainloop(){
	while(true){
		
	for (int i=0;i<=5;i++){
			SET_BIT(PORTB,i);
			segment(i);
			_delay_ms(200);
			CLEAR_BIT(PORTB,i);
	}
	for (int i=0;i<=0;i++){
			SET_BIT(PORTD,i+5);
			segment(i+6);
			_delay_ms(200);
			CLEAR_BIT(PORTD,i+5);
		}
		
	for (int i=1;i>=0;i--){
		SET_BIT(PORTD,i+5);
		segment(i+5);
		_delay_ms(200);
		CLEAR_BIT(PORTD,i+5);
	}
	for (int i=5;i>=0;i--){
		SET_BIT(PORTB,i);
		segment(i);
		_delay_ms(200);
		CLEAR_BIT(PORTB,i);
	}	
	}
		
}

int main (){
	mainloop();
}
