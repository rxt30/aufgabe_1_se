// This code waits for a character and transmits the character back (with interrupts)
#include "../sharedLibs/sharedFunctions.h"

volatile char receivedChar;

int main(void){
    serialInit();
    
    while(1){
        if(receivedChar != 0){
            sendChar(receivedChar);
            sendString("\r\n");
            receivedChar = 0;
        }
    }    
}

ISR (USART_RX_vect){
    receivedChar = UDR0;                       // Read data from the RX buffer
}