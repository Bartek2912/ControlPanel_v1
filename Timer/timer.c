#include "timer.h"


// ****** TIMER INTERRUPT ENABLE ******
void timer0InterruptEnable()
{
	TIMSK0 |= (1<<OCIE0A);
}


// ****** TIMER INTERRUPT DISABLE ******
void timer0InterruptDisable()
{
	TIMSK0 &= ~(1<<OCIE0A);
}


// ****** TIMER INIT ******
void timer0Init()
{
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS02) | (1<<CS00);
	OCR0A = TIME10MS; // 10ms
}

