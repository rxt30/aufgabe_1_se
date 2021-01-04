#ifndef INIT_HEADER
#define INIT_HEADER
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#ifndef BAUD
#define BAUD 9600
#define MYUBBR F_CPU/16/BAUD -1
#endif

#define SET_BIT(PORT,BIT) PORT |= (1<<BIT)
#define CLEAR_BIT(PORT,BIT) PORT &= ~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^= (1 << BIT)
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
void outputInit(int);
void interruptInit();
void serialInit();
void timerInit(bool,int,int);
void pwmInputInit(bool);
void pwmOutputInit(int,int);
void sendChar(char);
void sendString(char*);
#endif