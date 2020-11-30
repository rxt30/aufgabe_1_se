// This code waits for a character and transmits the character back (with interrupts)
 

#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t

#include <avr/interrupt.h>



#define F_CPU 16000000UL
#define BAUD 9600 
#define MYUBRR F_CPU/16/BAUD -1


volatile char ReceivedChar;
void send(char letter){
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = letter;
}


void sendString(char* letterBuffer){
    while(*letterBuffer){
        send(*letterBuffer++);
    }
    
}

int main( void )
{
    /*Set baud rate */
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;
    
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0B |= (1 << RXCIE0);                    // Enable reciever interrupt
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp

    sei();                                      // Lets not forget to enable interrupts =P
    char outputString[] = "Hello World\n\r";
    while(1)
    {
        sendString(outputString);                                     // Main loop
    }    
}

ISR (USART_RX_vect)
{
    ReceivedChar = UDR0;                       // Read data from the RX buffer
    UDR0 = ReceivedChar;                       // Write the data to the TX buffer
}

