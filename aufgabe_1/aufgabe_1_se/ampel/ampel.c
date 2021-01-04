#include "../sharedLibs/sharedFunctions.h"
#include <util/delay.h>

void mainloop() {
    SET_BIT(PORTB, PORTB0);
    _delay_ms(1000);
    SET_BIT(PORTB, PORTB1);
    _delay_ms(500);
    CLEAR_BIT(PORTB, PORTB0);
    CLEAR_BIT(PORTB, PORTB1);
    SET_BIT(PORTB, PORTB2);
    _delay_ms(1000);
    CLEAR_BIT(PORTB, PORTB2);
    SET_BIT(PORTB, PORTB1);
    _delay_ms(500);
    CLEAR_BIT(PORTB, PORTB1);

}

int main() {
    outputInit(3);
    while (1) {
        mainloop();
    }
}
