#include "buttons.h"
#include "../Outputs/outputs.h"
#include "../User_Interface/ui.h"
#include <avr/io.h>
#include <stdlib.h>


// ****** SOFTWARE TIMERS   ******
volatile uint16_t Timer1, Timer2, Timer3, Timer4;


// ****** DECLARATION OF BUTTONS ******
TBUTTON button1;
TBUTTON button2;
TBUTTON button3;
TBUTTON button4;


// ****** FUNCTIONS PERFORMED BY THE BUTTONS ******
void changed_output1(void) {
	outputChangeState(1);
	bmp_update();
}

void changed_output2(void) {
	outputChangeState(2);
bmp_update();
}

void changed_output3(void) {
	
	outputChangeState(3);
	bmp_update();
}

void changed_output4(void) {
	
	outputChangeState(4);
	bmp_update();
}


// ****** INITIALISING BUTTONS ******
void buttons_init(void) {
	// KEY1
	PORTC |= KEY1;
	button1.KPIN = &PINC;
	button1.key_mask = KEY1;
	button1.wait_time_ms = 20;
	button1.kfun1 = NULL;
	button1.kfun2 = changed_output1;
	button1.klock = 0;
	button1.flag = 0;
	button1.timer = &Timer1;
	
	// KEY1
	PORTC |= KEY2;
	button2.KPIN = &PINC;
	button2.key_mask = KEY2;
	button2.wait_time_ms = 20;
	button2.kfun1 = NULL;
	button2.kfun2 = changed_output2;
	button2.klock = 0;
	button2.flag = 0;
	button2.timer = &Timer2;
	
	// KEY1
	PORTC |= KEY3;
	button3.KPIN = &PINC;
	button3.key_mask = KEY3;
	button3.wait_time_ms = 20;
	button3.kfun1 = NULL;
	button3.kfun2 = changed_output3;
	button3.klock = 0;
	button3.flag = 0;
	button3.timer = &Timer3;
	
	// KEY1
	PORTC |= KEY4;
	button4.KPIN = &PINC;
	button4.key_mask = KEY4;
	button4.wait_time_ms = 20;
	button4.kfun1 = NULL;
	button4.kfun2 = changed_output4;
	button4.klock = 0;
	button4.flag = 0;
	button4.timer = &Timer4;
}


// ****** BUTTON CHECKING ******
void key_press(TBUTTON *btn) {
	register uint8_t key_press = !(*btn->KPIN & btn->key_mask);
	
	if(!btn->klock && key_press) {
		// SHORT PRESS RESPONSE 
		if(btn->kfun1) btn->kfun1();
		btn->flag = 1;
		*btn->timer = (btn->wait_time_ms) / 10;
		btn->klock = 1;
		} else if(btn->klock && key_press) {
		btn->klock++;
		if(!btn->klock) {
			*btn->timer = 0;
			btn->flag = 0;
		}
		} else if(btn->flag && !(*btn->timer)) {
		// RESPONSE TO LONG PRESSING 
		if(btn->kfun2) btn->kfun2();
		btn->flag = 0;
		btn->klock = 0;
		} else if(!key_press) {
		btn->klock = 0;
	}
}
