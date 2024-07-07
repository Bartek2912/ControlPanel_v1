#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#include "../OLED_SSD1309/ssd1309.h"
#include "ui.h"
#include "../Buttons/buttons.h"
#include "../Outputs/outputs.h"

// ****** DRAWS THE START SCREEN ******
void loadScreen(void)
{
	ssd1309_cls();  
	ssd1309_drawBitmap(0, 0, bmp_startScreen, 128, 64, 1);
	ssd1309_puts(38, page2 * 8, "Ladownie", 1, 1, 0);
	ssd1309_display(); 
	ssd1309_loadingBar(1, 126, 28, 34);
	ssd1309_puts(14, page2 * 8, "Panel oswietlenia", 1, 1, 0);
	ssd1309_refresh_pages(page2, 1, 0, 127);
	ssd1309_cls();
}

// ****** DRAWS THE MAIN SCREEN ******
void mainScreen(void)
{
	ssd1309_display();
	ssd1309_drawBitmap(0,0,bmp_main,128,64,1); 

	ssd1309_puts(14, 51, "F1", 1, 1, 0);
	ssd1309_puts(44, 51, "F2", 1, 1, 0);
	ssd1309_puts(74, 51, "F3", 1, 1, 0);
	ssd1309_puts(104, 51, "F4", 1, 1, 0);
	
	ssd1309_puts(3, 2, "Parametry:", 1, 1, 0);
	ssd1309_puts(3, 12, "Temp:", 1, 1, 0);
	ssd1309_puts(3, 20, "Wilg:", 1, 1, 0);
	ssd1309_refresh_pages(page0, page7 + 1, 0, 128);
	
	bmpUpdate_frontLightsOFF();
	bmpUpdate_frontHalogenOFF();
	bmpUpdate_reverseHalogenOFF();
	bmpUpdate_signalOFF();

}

// ****** UPDATE DHT VALUE ******
void dht_update(uint16_t readValue, uint8_t y )
{
	unsigned char ten_count = 0;
	unsigned char hun_count = 0;
	
// ****** RECALCULATION OF VALUES ******
	
	while(readValue >= 100){ // READING THE DECIMAL VALUE  | EXAMPLE 235 -> 2
		hun_count++;
		readValue -=100;
	}
	ssd1309_puts_int(34,y,hun_count,1,1,0); 
	
	while(readValue >= 10){ // READING THE UNITY VALUE  | EXAMPLE 235 -> 3
		ten_count++;
		readValue -=10;
	}
	ssd1309_puts_int(40,y,ten_count,1,1,0); 
	ssd1309_puts(45,y,".",1,1,0); // DISPLAYING A DOT 
	
	ssd1309_puts_int(50,y,readValue,1,1,0); // DISPLAY OF THE DIGIT AFTER THE DECIMAL POINT | 235 -> 5
	// RESULT -> 23.5 
}

// ****** UPDATE ICONS ******
void bmp_update(void)
{
	if(OUT1_PIN & OUT1)
	{
		bmpUpdate_frontLightsON();
	}
	else
	{
		bmpUpdate_frontLightsOFF();
	}
	
	if(OUT2_PIN & OUT2)
	{
		bmpUpdate_frontHalogenON();
	}
	else
	{
		bmpUpdate_frontHalogenOFF();
	}
	
	if(OUT3_PIN & OUT3)
	{
		bmpUpdate_signalON();
	}
	else
	{
		bmpUpdate_signalOFF();
	}
	
	if(OUT4_PIN & OUT4)
	{
		bmpUpdate_reverseHalogenON();
	}
	else
	{
		bmpUpdate_reverseHalogenOFF();
	}
}


// ****** BITMAP UPDATE FUNCTION ******
void bmpUpdate_frontLightsON(void)
{
	ssd1309_drawBitmap(78,22,bmp_LightsON,8,8,1); 
	ssd1309_refresh_pages(page1, page5, 77, 87);
}

void bmpUpdate_frontLightsOFF(void)
{
	ssd1309_drawBitmap(78,22,bmp_LightsON,8,8,0);
	ssd1309_drawBitmap(78,22,bmp_LightsOFF,8,8,1); 
	ssd1309_refresh_pages(page1, page5, 77, 87);
}

void bmpUpdate_frontHalogenON(void)
{
	ssd1309_drawBitmap(96, 14, bmp_LightsON, 8, 8, 1);
	ssd1309_refresh_pages(page1, page5, 95, 105);
}

void bmpUpdate_frontHalogenOFF(void)
{
	ssd1309_drawBitmap(96, 14, bmp_LightsON, 8, 8, 0);
	ssd1309_drawBitmap(96, 14, bmp_LightsOFF, 8, 8, 1); 
	ssd1309_refresh_pages(page1, page5, 95, 105);
}

void bmpUpdate_reverseHalogenON(void)
{
	ssd1309_drawBitmap(117, 14, bmp_reverseLightsON, 8, 8, 1); 
	ssd1309_refresh_pages(page1, page5, 116, 126);
}

void bmpUpdate_reverseHalogenOFF(void)
{
	ssd1309_drawBitmap(117, 14, bmp_reverseLightsON, 8, 8, 0); 
	ssd1309_drawBitmap(117,14,bmp_reverseLightsOFF,8,8,1); 
	ssd1309_refresh_pages(page1, page5, 116, 126);
}

void bmpUpdate_signalON(void)
{
	ssd1309_drawBitmap(106, 10, bmp_signalON, 8, 8, 1); 
	ssd1309_refresh_pages(page0, page5, 105, 114);
}

void bmpUpdate_signalOFF(void)
{
	ssd1309_drawBitmap(106, 10, bmp_signalON, 8, 8, 0);
	ssd1309_drawBitmap(106, 10, bmp_signalOFF, 8, 8, 1); 
	ssd1309_refresh_pages(page0, page5, 105, 114);
}