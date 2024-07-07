#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "OLED_SSD1309/ssd1309.h"
#include "User_Interface/ui.h"
#include "Outputs/outputs.h"
#include "Timer/timer.h"
#include "Buttons/buttons.h"
#include "DHT_Sensor/DHT.h"

// ****** SOFTWARE TIMERS   ******
volatile uint16_t Timer1, Timer2, Timer3, Timer4, Timer5;


uint16_t temperature_int = 0;
uint16_t humidity_int = 0;

int main(void) {
	// ****** INITIALISATION OF PERIPHERALS ******
	outputInit();
	buttons_init();
	timer0Init();
	timer0InterruptEnable();
	sei();
	
	ssd1309_init(SSD1309_SWITCHCAPVCC, REFRESH_MAX);
	ssd1309_cls();
	ssd1309_display();
	
	// ****** LOADING SCREEN ******
	loadScreen();
	_delay_ms(1000);
	mainScreen();
	
	while (1) {
		// ****** CHECKING THE BUTTONS ******
		 key_press(&button1);
		 key_press(&button2);
		 key_press(&button3);
		 key_press(&button4);
		 
		 // ****** DISPLAY OF TEMPERATURE AND HUMIDITY  ******
		 if(!Timer5)
		 {
			 Timer5 = 400;
		 
			if (dht_GetTempUtil(&temperature_int, &humidity_int) != -1) {
				dht_update(temperature_int, 12 );
				dht_update(humidity_int, 20 );
				ssd1309_refresh_pages(page0,page5,0,64);
			}
	
		}
		
	}
	
}


ISR(TIMER0_COMPA_vect) {
	uint16_t n;
	
	n = Timer1;
	if(n) Timer1 = --n;
	
	n = Timer2;
	if(n) Timer2 = --n;

	n = Timer3;
	if(n) Timer3 = --n;

	n = Timer4;
	if(n) Timer4 = --n;
	
	n = Timer5;
	if(n) Timer5 = --n;
}