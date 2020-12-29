#include "../sharedLibs/sharedFunctions.h"

#define TOGGLE_BIT(PORT,BIT) PORT ^= (1<<BIT)

void mainloop() {
    TOGGLE_BIT(PORTB, PORTB0)
    _delay_ms(1000)
    TOGGLE_BIT(PORTB, PORTB1)
    _delay_ms(500)
    TOGGLE_BIT(PORTB, PORTB0)
    TOGGLE_BIT(PORTB, PORTB1)
    TOGGLE_BIT(PORTB, PORTB2)
    _delay_ms(1000)
    TOGGLE_BIT(PORTB, PORTB2)
    TOGGLE_BIT(PORTB, PORTB1)
    _delay_ms(500)
    TOGGLE_BIT(PORTB, PORTB1)
}

int main() {
    init(3, false);
    while (1) {
        mainloop()
    }
}