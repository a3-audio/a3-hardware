/*
 * init.h
 *
 * Created: 17/03/2022 12:17:46
 *  Author: tirii
 */ 


#ifndef INIT_H_
#define INIT_H_
#define N_RGB_BUTTON	4
#include "hardware.h"
#include "bitoperation.h"
#include <avr/io.h>
#include <math.h>

#define ADC_TIMEBASE	((uint8_t)ceil(F_CPU*0.000001))
#define STATE_BUT_PRESSED	0xFF
#define STATE_BUT_RELEASED	0
typedef struct
{
	uint8_t state;
	uint8_t	sample;
}button;

void encode_init(int8_t *last,int8_t *enc_delta);
void button_init(button buttons[]);
void led_bus_init();
void timer0_init();
void timer1_init();
void i2c_init();
void i2c_slave_init();


#endif /* INIT_H_ */
