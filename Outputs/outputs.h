#include <avr/io.h>
#ifndef OUTPUTS_H_
#define OUTPUTS_H_


// ****** OUTPUT PIN DECLARATIONS ******
#define OUT1 (1<<2)
#define OUT2 (1<<3)
#define OUT3 (1<<4)
#define OUT4 (1<<5)

#define OUT1_PORT PORTD
#define OUT1_DDR DDRD
#define OUT1_PIN PIND

#define OUT2_PORT PORTD
#define OUT2_DDR DDRD
#define OUT2_PIN PIND

#define OUT3_PORT PORTD
#define OUT3_DDR DDRD
#define OUT3_PIN PIND

#define OUT4_PORT PORTD
#define OUT4_DDR DDRD
#define OUT4_PIN PIND

#define OUT1_LO OUT1_PORT &= ~OUT1
#define OUT1_HI OUT1_PORT |= OUT1
#define OUT1_REV OUT1_PORT ^= OUT1

#define OUT2_LO OUT2_PORT &= ~OUT2
#define OUT2_HI OUT2_PORT |= OUT2
#define OUT2_REV OUT2_PORT ^= OUT2

#define OUT3_LO OUT3_PORT &= ~OUT3
#define OUT3_HI OUT3_PORT |= OUT3
#define OUT3_REV OUT3_PORT ^= OUT3

#define OUT4_LO OUT4_PORT &= ~OUT4
#define OUT4_HI OUT4_PORT |= OUT4
#define OUT4_REV OUT4_PORT ^= OUT4


// ****** VARIABLE DECLARATION ******


//  ****** FUNCTION DECLARATION ******
void outputInit(void);
void outputChangeState(char out);

#endif /* OUTPUTS_H_ */