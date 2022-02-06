/*
* MCU.c
*
* Created: 23/01/2022 00:13:26
* Author : Felix Dahmen
*/

#define F_CPU 1E6
#include <util/delay.h>
#include <avr/io.h>
#include "main.h"
#include <avr/interrupt.h>



#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

#define PSHFDATA 1  //B O
#define PSHFCLK 2  //B O
#define PSHFUPDATE 3  //B O

#define PENCA 6  //B I
#define PENCB 7  //B I
#define PENSCW 5  //A I

#define PSDA 0  //A
#define PSCL 2  //A

#define BUT0 0  //B I
#define BUT1 4  //A  I
#define BUT2 3  //A I
#define BUT3 1  //A I

#define PADC0 6  //A I
#define PADC1 7  //A I
#define func(A) writeSPI4(A)

#define RED PA1
#define BLUE PA3
#define GREEN PA4


#define RGB_COLORS (sizeof(rgb_r)/sizeof(rgb_r[0])) //must be multiple of 4
#define RGB_LEVELS 15 //number of brightness levels 

volatile uint8_t rgb_counter=2;
volatile uint8_t rgb_brightness=5;
volatile uint8_t rgb_color=0;

int intr_count=0;
int sec=0;

ISR (TIMER0_OVF_vect)      //Interrupt vector for Timer0
{
		rgb_out();
		//PORTB^=(1<<RED); //toggling the LED
		//uint16_t start_val= - 4; //5000us/256us/200Hz
		//TCNT0H=(uint8_t)(start_val>>8);
		TCNT0L=-4;
}
ISR (ADC_vect)
{
	uint16_t adcval=ADCL;
	uint16_t adcval2=(ADCH<<8)|adcval;
	//adcval|=ADCH;
	//uint8_t val=adcval/(UINT16_MAX/14)+2;
	if (adcval2>=2)
	{
		rgb_color=2;
	}else{
		rgb_color=14;
	}
	//rgb_color=val;
			//rgb_color=++rgb_color;
			//rgb_color=rgb_color%RGB_COLORS;
			//if(!rgb_color)rgb_color=2;
}

void timer_setup()
{
	TCCR0A=0x00;   //Normal mode 8bit counter
	TCCR0B=0x00;
	TCCR0B |= (1<<CS02);   //prescaling with 1024
	sei(); //enabling global interrupt
	//uint8_t start_val= - 4;
	//TCNT0H=(uint8_t)(start_val>>8);
	TCNT0L=-4;
	TIMSK|=(1<<TOIE0); //enabling timer0 interrupt
}

void adc_setup(){
  ADMUX =
  (1 << ADLAR) |     // left shift result
  (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
  (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
  (0 << MUX4)  |     // use ADC2 for input (PB4), MUX bit 3
  (0 << MUX3)  |     // use ADC2 for input (PB4), MUX bit 3
  (1 << MUX2)  |     // use ADC2 for input (PB4), MUX bit 2
  (1 << MUX1)  |     // use ADC2 for input (PB4), MUX bit 1
  (0 << MUX0);       // use ADC2 for input (PB4), MUX bit 0

  ADCSRA =
  (1 << ADEN)  |     // Enable ADC
  (1 << ADPS2) |     // set prescaler to 64, bit 2
  (1 << ADPS1) |     // set prescaler to 64, bit 1
  (0 << ADPS0);      // set prescaler to 64, bit 0
  
  ADCSRB=(0<<MUX5);
}
void rgb_out(){
	uint8_t r=rgb_r[rgb_color]*rgb_brightness;
	uint8_t g=rgb_g[rgb_color]*rgb_brightness;
	uint8_t b=rgb_b[rgb_color]*rgb_brightness;
	uint8_t mask=(1<<RED)|(1<<BLUE)|(1<<GREEN);
	uint8_t PORT_temp=((PORTA&~mask));
	PORT_temp|=((r>rgb_counter)<<RED)|((g>rgb_counter)<<GREEN)|((b>rgb_counter)<<BLUE);
	PORTA=PORT_temp;
	rgb_counter++;
	rgb_counter = rgb_counter % RGB_LEVELS;

}

void writeSPI4(uint8_t val)
{
    USIDR = val;
    USISR = (1<<USIOIF);   //resets counter, clears flag
    do {
	    USICR = (1<<USIWM0)|(0<<USICS0)|(1<<USICLK)|(1<<USITC);
		_delay_ms(1);
    } while ((USISR & (1<<USIOIF)) == 0);
}
/*
ADCSRA
ADEN: ADC Enable
ADSC starts conversion
This bit stays high as long as the conversion is in progress
If a different data channel is selected while a conversion is in
progress, the ADC will finish the current conversion before performing the channel change.
ADPS2:0: bits
sample frequency 50-200khz
A normal conversion takes 13 ADC clock cycles.
ADIF: ADC Interrupt Flag
 ADIE: ADC Interrupt Enable

ADCSRB
MUX5:0 channel select
REFS2:0 reference select


After the conversion is complete (ADIF is high), the conversion result can be found in the ADC
Result Registers (ADCL, ADCH).

ADMUX
REFS1:REFS0 0 0 heisst Vcc ref
MUX4:0 0-10 geben input pin PA0-PA7;PB4-PB7

ADCL and ADCH – The ADC Data Register
*/
int main(void)
{
	//setup
	//DDRB=(1<<PSHFDATA)|(1<<PSHFCLK);
	uint8_t temp_color=0;
	DDRA=(1<<RED)|(1<<BLUE)|(1<<GREEN);
	//CLEARBIT(USIPP,0);
	adc_setup();
	timer_setup();
	while (1)
	{

		//_delay_ms(100);
		//ADCSRA|=(1<<ADSC);
		ADCSRA |= (1 << ADSC);         // start ADC measurement
		while (ADCSRA & (1 << ADSC) ); // wait till conversion complete

		if (ADCH > 128)
		{
			rgb_color=2;


			} else {
			rgb_color=14;

		}
		_delay_ms(100);
		uint8_t t= rgb_color;
		rgb_color=8;
		_delay_ms(100);
		
		rgb_color=t;
		_delay_ms(1000);
		
	}
	
}

