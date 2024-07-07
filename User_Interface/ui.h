#include <avr/io.h>
#ifndef UI_H_
#define UI_H_

// ****** bitmap.c ******
extern const uint8_t bmp_clear [];
extern const uint8_t bmp_LightsON [];
extern const uint8_t bmp_LightsOFF [];
extern const uint8_t bmp_reverseLightsON [];
extern const uint8_t bmp_reverseLightsOFF [];
extern const uint8_t bmp_signalON [];
extern const uint8_t bmp_signalOFF [];
extern const uint8_t bmp_logo [];
extern const uint8_t bmp_temperature [];
extern const uint8_t bmp_startScreen [];
extern const uint8_t bmp_tractor [];
extern const uint8_t bmp_main [];


// ****** UI FUNCTION ******
// ****** ui.c ******
void loadScreen(void);
void mainScreen(void);
void bmp_update();
void dht_update(uint16_t readValue, uint8_t y );

// ****** BITMAP UPDATE FUNCTION ******
void bmpUpdate_frontLightsON(void);
void bmpUpdate_frontLightsOFF(void);

void bmpUpdate_frontHalogenON(void);
void bmpUpdate_frontHalogenOFF(void);

void bmpUpdate_reverseHalogenON(void);
void bmpUpdate_reverseHalogenOFF(void);

void bmpUpdate_signalON(void);
void bmpUpdate_signalOFF(void);


#endif /* UI_H_ */