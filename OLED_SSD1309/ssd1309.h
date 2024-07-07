#include <avr/io.h>
#ifndef SSD1309_H_
#define SSD1309_H_

#define SSD1309_128_64

#define USE_CS 1
#define USE_RST 1

#define swap(a, b) {int16_t t = a; a = b; b = t; }
typedef enum{page0, page1, page2, page3, page4, page5, page6, page7} TARGET;

// ****** SOFT SPI PIN DECLARATIONS ******
#define  SCK (1<<5) 
#define MOSI (1<<3) 
#define  RST (1<<0) 
#define DC (1<<1) 
#define CS (1<<2) 

#define SCK_PORT PORTB
#define SCK_DDR DDRB

#define MOSI_PORT PORTB
#define MOSI_DDR DDRB

#define RST_PORT PORTB
#define RST_DDR DDRB

#define DC_PORT PORTB
#define DC_DDR DDRB

#define CS_PORT PORTB
#define CS_DDR DDRB

#define SCK_LO SCK_PORT &= ~SCK
#define SCK_HI SCK_PORT |= SCK

#define MOSI_LO MOSI_PORT &= ~MOSI
#define MOSI_HI MOSI_PORT |= MOSI

#define RST_LO RST_PORT &= ~RST
#define RST_HI RST_PORT |= RST

#define DC_LO DC_PORT &= ~DC
#define DC_HI DC_PORT |= DC

#define CS_LO CS_PORT &= ~CS
#define CS_HI CS_PORT |= CS


// ****** DISPLAY SIZE ******
#define  SSD1309_WIDTH 128
#define  SSD1309_HEIGHT 64 
#define BUFF_SIZE 1024

// ******* SCREEN REFRESH RATE ******
#define  REFRESH_MIN 0x80
#define  REFRESH_MID 0xB0
#define  REFRESH_MAX 0xF0


// ****** DISPLAY COMMAND ******
#define SSD1309_SETCONTRAST 0x81
#define SSD1309_DISPLAYALLON_RESUME 0xA4
#define SSD1309_DISPLAYALLON 0xA5
#define  SSD1309_NORMALDISPLAY 0xA6
#define SSD1309_INVERTDISPLAY 0xA7
#define SSD1309_DISPLAYOFF 0xAE
#define SSD1309_DISPLAYON 0xAF

#define SSD1309_SETDISPLAYOFFSET 0xD3
#define SSD1309_SETCOMPINS 0xDA

#define SSD1309_SETVCOMIDETECT 0xDB

#define SSD1309_SETDISPLAYCLOCKDIV 0xD5
#define SSD1309_SETPRECHARGE 0xD9

#define SSD1309_SETMULTIPLEX 0xA8

#define SSD1309_SETLOWCOLUMN 0x00
#define SSD1309_SETHIGHCOLUMN 0x10

#define SSD1309_SETSTARTLINE 0x40 

#define SSD1309_MEMORYMODE 0x20

#define SSD1309_COMSCANINC 0xC0
#define SSD1309_COMSCANDEC 0xC8

#define SSD1309_CHARGEPUMP 0x8D

#define SSD1309_EXTERNALVCC 0x01
#define SSD1309_SWITCHCAPVCC 0x02

#define SSD1309_ACTIVE_SCROLL 0x2F
#define SSD1309_DEACTIVATE_SCROLL 0x2E
#define SSD1309_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1309_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1309_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1309_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1309_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

#define SSD1309_SEGREMAP 0xA0 // 0XA1


// ****** VARIABLE DECLARATION ******

extern const uint8_t font[]; // olde_font.c





//  ****** FUNCTION DECLARATION ******

// ****** BASIC CONTROLLER FUNCTION ******
// ****** ssd1309.c ******
void ssd1309_init(uint8_t vcc, uint8_t refresh);
void ssd1309_data(uint8_t dat);
void ssd1309_cmd(uint8_t cmd);

void ssd1309_display(void);
void ssd1309_refresh_pages(uint8_t page_nr, uint8_t page_cnt, uint8_t col_start, uint8_t col_end);
void ssd1309_setPixel(int x, int y, uint8_t bw);
void ssd1309_cls(void);


// ****** GRAPHIC FUNCTION ******
// ****** graphic.c ******
void ssd1309_drawBitmap(int x, int y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);

void ssd1309_drawChar(int x, int y, char c, uint8_t color, uint8_t bg, uint8_t size);
void ssd1309_puts(int x, int y, char * str, uint8_t txt_size, uint8_t color, uint8_t bg);
void ssd1309_puts_int(int x, int y, int data, uint8_t txt_size, uint8_t color, uint8_t bg);

void ssd1309_fillRect(int x, int y, int w ,int h, uint8_t color);
void ssd1309_drawFastVLine(int x,int y,int h, uint8_t color);
void ssd1309_drawLine(int x0,int y0,int x1, int y1, uint8_t color);
void ssd1309_loadingBar(uint8_t x_start, uint8_t x_stop, uint8_t y_start, uint8_t y_stop);


#endif /* SSD1309_H_ */