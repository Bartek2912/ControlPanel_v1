#include "ssd1309.h"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h>


// ****** BUFOR ******
uint8_t ssd1309_buf[BUFF_SIZE] = {

};


// ****** SPI SEND DATA ******
static void SPIwrite(uint8_t dat)
{
	uint8_t i;
	for(i = 0x80; i; i>>=1)
	{
		SCK_LO;
		if(dat & i) MOSI_HI;
		else MOSI_LO;
		SCK_HI;
	}
}


// ******SEND COMMAND ******
void ssd1309_cmd(uint8_t cmd)
{
#if USE_CS == 1
	CS_HI;
#endif

	DC_LO;
	
#if USE_CS == 1
	CS_LO;
#endif

	SPIwrite(cmd);
	
#if USE_CS == 1
	CS_HI;
#endif
}


// ****** SEND DATA ******
void ssd1309_data(uint8_t dat)
{
#if USE_CS == 1
	SCK_HI;
#endif

	DC_HI;

#if USE_CS == 1
	CS_LO;
#endif
	
	SPIwrite(dat);

#if USE_CS == 1
	SCK_HI;
#endif
}


// ****** DISPLAY DATA ******
void ssd1309_display(void)
{
	ssd1309_cmd(SSD1309_SETLOWCOLUMN | 0x0);   // low col = 0
	ssd1309_cmd(SSD1309_SETHIGHCOLUMN | 0x0);  // hi col = 0
	ssd1309_cmd(SSD1309_SETSTARTLINE | 0x0);   // line #0

	for (uint16_t i = 0; i<(SSD1309_WIDTH*SSD1309_HEIGHT/8); i++) {
		ssd1309_data(ssd1309_buf[i]);
	}
}


// ****** SET PIXEL ******
void ssd1309_setPixel(int x, int y, uint8_t bw)
{
	if((x < 0 ) || (x>=SSD1309_WIDTH) || (y>=SSD1309_HEIGHT))
	return;
	if(bw) ssd1309_buf[x + (y/8) * SSD1309_WIDTH] |= (1<<y%8);
	else ssd1309_buf[x + (y/8) * SSD1309_WIDTH] &= ~(1<<y%8);
}


// ****** CLEAR DISPLAY BUFFER ******
void ssd1309_cls(void)
{
	memset(ssd1309_buf, 0x00, (BUFF_SIZE));
}




// ****** SPI INIT ******
void ssd1309_InitSpi(void)
{
	MOSI_DDR |= MOSI;
	
	SCK_DDR |=SCK;
	SCK_PORT |=SCK;
	
#if USE_RST == 1	
	RST_DDR |= RST;
	RST_PORT |= RST;
#endif	
	DC_DDR |= DC;

#if USE_CS == 1
	CS_DDR |= CS;
	CS_PORT |= CS;
#endif

}


// ****** SSD1309 INIT AND CLEAR DISPLAY ******
void ssd1309_init(uint8_t vcc, uint8_t refresh)
{
	ssd1309_InitSpi();
#if USE_RST == 1
	RST_HI;
	_delay_ms(200);
	RST_LO;
	_delay_ms(200);
	RST_HI;
#endif

#if USE_CS == 1
	CS_HI;
	_delay_ms(200);
	CS_LO;
	_delay_ms(200);
	CS_HI;
#endif
	
	ssd1309_cmd(SSD1309_DISPLAYOFF);
	ssd1309_cmd(SSD1309_SETDISPLAYCLOCKDIV);
	ssd1309_cmd(refresh);
	
	ssd1309_cmd(SSD1309_SETDISPLAYOFFSET);
	ssd1309_cmd(0x0);
	ssd1309_cmd(SSD1309_SETSTARTLINE | 0x0); // 
	ssd1309_cmd(SSD1309_SETPRECHARGE);
	
	if(vcc == SSD1309_EXTERNALVCC) ssd1309_cmd(0x10);
	else ssd1309_cmd(0x14);
	
	ssd1309_cmd(SSD1309_MEMORYMODE);
	ssd1309_cmd(0x00);
	ssd1309_cmd(SSD1309_SEGREMAP | 0x1);
	ssd1309_cmd(SSD1309_COMSCANDEC);
	
	ssd1309_cmd(SSD1309_SETCONTRAST);
	
	if(vcc == SSD1309_EXTERNALVCC) ssd1309_cmd(0x9F);
	else ssd1309_cmd(0xCF);
	
	ssd1309_cmd(SSD1309_SETPRECHARGE);
	
	ssd1309_cmd(SSD1309_SETMULTIPLEX);
	ssd1309_cmd(0x3F);

	ssd1309_cmd(SSD1309_SETCOMPINS);
	ssd1309_cmd(0x12);
	
	ssd1309_cmd(SSD1309_DISPLAYALLON_RESUME);
	ssd1309_cmd(SSD1309_NORMALDISPLAY);
	ssd1309_cmd(SSD1309_DISPLAYON);
	ssd1309_cls();
	ssd1309_display();
}


// ****** SSD1309 PAGE REFRESH ******
void ssd1309_refresh_pages(uint8_t page_nr, uint8_t pages_cnt, uint8_t col_start, uint8_t col_end)
{
	uint8_t page_cnt, col_cnt;
	uint8_t *ram_buf_start;

	for (page_cnt = page_nr; page_cnt < (page_nr + pages_cnt); page_cnt++)
	{
		ssd1309_cmd(SSD1309_SETLOWCOLUMN | (col_start & 0x0F));
		ssd1309_cmd(SSD1309_SETHIGHCOLUMN | (col_start >> 4));
		ssd1309_cmd(0xB0 + page_cnt);  

		ram_buf_start = &ssd1309_buf[(page_cnt * 128) + col_start];

		for (col_cnt = col_start; col_cnt < col_end; col_cnt++)
		{
			ssd1309_data(*ram_buf_start++);
		}
	}
}
