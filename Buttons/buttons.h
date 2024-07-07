#ifndef BUTTONS_H
#define BUTTONS_H

#include <avr/io.h>

// ****** BUTTON MACROS  ******
#define  KEY1 (1<<PC0)
#define  KEY2 (1<<PC1)
#define  KEY3 (1<<PC2)
#define  KEY4 (1<<PC3)

// ****** STRUCTURE OF BUTTON STATUS ******
typedef struct {
	volatile uint8_t *KPIN;
	uint8_t key_mask;
	uint8_t wait_time_ms;
	void (*kfun1) (void);
	void (*kfun2) (void);
	uint8_t klock;
	uint8_t flag;
	volatile uint16_t *timer;
} TBUTTON;

// ****** DECLARATION OF BUTTONS ******
extern TBUTTON button1;
extern TBUTTON button2;
extern TBUTTON button3;
extern TBUTTON button4;

// ****** FUNCTION DECLARATION ******
void buttons_init(void);
void key_press(TBUTTON *btn);

#endif // BUTTONS_H
