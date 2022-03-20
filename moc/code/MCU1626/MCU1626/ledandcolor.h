/*
 * colormath.h
 *
 * Created: 16/03/2022 13:13:26
 *  Author: tirii
 */ 


#ifndef COLORMATH_H_
#define COLORMATH_H_
#include <stdint.h>
#include "bitoperation.h"
#include "hardware.h"
typedef struct{
	uint16_t shiftVal;
	uint8_t time;
} ledEvent;

typedef	struct{
	uint8_t	position;
	uint8_t time;
}led;

 typedef struct
 {
	 led	red;
	 led	green;
	 led	blue;
 }rgbLed;
 
void updateRGBLed(uint8_t number,uint16_t angle,uint8_t value);
void rgb_led_init();
void hsvtoRGB (rgbLed *regButton,float angle, uint8_t val);
void updateColorSystem(rgbLed regButton,led leds[],ledEvent led_events[],uint8_t *nLed_event);
int ledCompare(const void *a, const void *b);
ledEvent getNextLedEvent();

#endif /* COLORMATH_H_ */
