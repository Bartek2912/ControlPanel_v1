#ifndef TIMER_H_
#define TIMER_H_


#include <avr/io.h>
// ****** VALUE 10 MS ******
#define TIME10MS 77


// ****** TIMER FUNCTIONS ******
void timer0Init();
void timer0InterruptEnable();
void timer0InterruptDisable();


#endif /* TIMER_H_ */