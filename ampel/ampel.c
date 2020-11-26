#include "../sharedLibs/sharedFunctions.h"

int main(){
    init(15,false);
    while(1){
        SET_BIT(PORTB,PORTB0);
        SET_BIT(PORTB,PORTB1);
        SET_BIT(PORTB,PORTB2);
    }
}
