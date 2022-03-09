/*
* MCU.c
*
* Created: 23/01/2022 00:13:26
* Author : Felix Dahmen

Header (NEW)
GND 11  GND 12  VCC 14  10  13  9
 -  PA7  -  PA6  -  PA4 PB7 PA5 PB6
    AD6     AD5     AD3 RS  AD4  -

AD1 ARE         SCL  -  DO   -  SDA
PA1 PA3  -   -  PB2 PB3 PB1  -  PB0
 19 17  VCC GND 3   4   2   GND 1

Header (OLD)
GND 11  GND 12  VCC 14  10  13  9
-  PA7  -  PA6  -  PA4 PB7 PA5 PB6
   AD6     AD5     AD3 RS  AD4  -

AD1 ARE         SCL  -  SDA  -  DO
PA1 PA3  -   -  PB2 PB3 PB0  -  PB1
 19 17  VCC GND 3   4   1   GND  2


COM Interface (OLD)
SDA GND VCC SCL GND



*/

#define F_CPU 8E6

#define DEVICE_ADDRESS	(4)

#include <util/delay.h>
#include <avr/io.h>
#include "main.h"
#include <avr/interrupt.h>
#include "usitwislave.h"
#include <stdint.h>
#include <avr/sleep.h>

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

#define PSDA PA0  //A XXX
#define PSCL PA2  //A

#define BUT0 0  //B I
#define BUT1 4  //A  I
#define BUT2 3  //A I
#define BUT3 1  //A I

#define PADC0 6  //A I
#define PADC1 7  //A I
#define N_ADC_BUFFER 32
uint8_t iAdcBuffer=0;
uint32_t adcval0;
uint16_t adcvalBuffer0[N_ADC_BUFFER];
static uint8_t test=0;

#define func(A) writeSPI4(A)

#define RED PA1
#define BLUE PA3
#define GREEN PA4

uint8_t timer1test=0;

#define RGB_COLORS (sizeof(rgb_r)/sizeof(rgb_r[0])) //must be multiple of 4
#define RGB_LEVELS 15 //number of brightness levels

typedef enum {
	I2C_REQUEST_ADC0=0x63,
	I2C_REQUEST_ADC1=0x95,
	I2C_IDLE=0
	}i2c_state;

volatile i2c_state i2cState=I2C_IDLE;

volatile uint8_t rgb_counter=2;
volatile uint8_t rgb_brightness=5;
volatile uint8_t rgb_color=0;


int intr_count=0;
int sec=0;

ISR (TIMER0_OVF_vect)      //Interrupt vector for Timer0
{
	
	//rgb_out();
	//PORTB^=(1<<RED); //toggling the LED
	//uint16_t start_val= - 4; //5000us/256us/200Hz
	//TCNT0H=(uint8_t)(start_val>>8);
	
			if((timer1test++)&1)
			PORTB|=(1<<PB6);
			else
			CLEARBIT(PORTB,PB6);
	TCNT0L=-80;
}
ISR (TIMER1_OVF_vect)      //Interrupt vector for Timer0
{
	
	//rgb_out();
	//PORTB^=(1<<RED); //toggling the LED
	//uint16_t start_val= - 4; //5000us/256us/200Hz
	//TCNT0H=(uint8_t)(start_val>>8);
	
	if((timer1test++)&1)
	PORTB|=(1<<PB6);
	else
	CLEARBIT(PORTB,PB6);
	TCNT1=-80;
	//set_sleep_mode(SLEEP_MODE_ADC);
}

ISR (ADC_vect)
{	
	//set_sleep_mode(SLEEP_MODE_IDLE);
	uint16_t adcval_temp=ADCL;
	adcval_temp|=(ADCH<<8);
	adcval0+=adcval_temp;
	adcval0-=adcvalBuffer0[(iAdcBuffer+1)%N_ADC_BUFFER];
	iAdcBuffer++;
	iAdcBuffer%=N_ADC_BUFFER;
	adcvalBuffer0[iAdcBuffer]=adcval_temp;
	ADCSRA|=(1<<ADIF);
	
	//adcval|=ADCH;
	//uint8_t val=adcval/(UINT16_MAX/14)+2;
}

void timer0_setup()
{

	
	TCCR0A=0x00;   //Normal mode 8bit counter
	TCCR0B=0x00;
	TCCR0B |= (1<<CS00);   //prescaling with 1024
	TCNT0L=-10;
	TIMSK|=(1<<TOIE0); //enabling timer0 interrupt

}

void timer1_setup()
{

	TCCR1A=0x00;   //Normal mode 8bit counter
	TCCR1B=0x00;
	TCCR1B |= (1<<CS11);   //prescaling with 2
	TCNT1=-10;
	TIMSK|=(1<<TOIE1); //enabling timer0 interrupt
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
void adc_setup(){
	ADMUX =
	(0 << ADLAR) |     // left shift result
	(0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
	(0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
	//MUX	0-6		a0 a1 a2 a4 a5 a6 a7 
	//		7-10	b4 b5 b6 b7
	(0 << MUX4)  |  (0 << MUX3)  |	(0 << MUX2)  |	(0 << MUX1)  |(1 << MUX0);       

	ADCSRA =
	(1 << ADEN)  |     // Enable ADC
	(1 << ADIE)  |     // ADC Interrupt Enable
	(1<<ADATE)	  |    // Auto triger enable this time timer 1 overflow
	(0 << ADPS2) |	(0 << ADPS1) |	(0 << ADPS0);	// prescaler system clock 
													//0,1:	2	2:	4	3:	8	4:	16
													//5:	32	6:	64	7:	128 
	
	ADCSRB=(0<<MUX5)|
			(1<<ADTS2)	|
			(1<<ADTS1)	|
			(0<<ADTS0);
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


uint8_t sendthis[]={1,2,3,4,5};
uint8_t regs[4] = { 4, 8, 16, 32 };
uint8_t currentReg = 0;


static void request(volatile uint8_t input_buffer_length, const uint8_t *input_buffer,
uint8_t *output_buffer_length, uint8_t *output_buffer) {
	// the number of bytes to be returned to the master
	*output_buffer_length = 2;
	//output_buffer[0] = 55;
	uint32_t adcValTemp=0;
	if(input_buffer_length>0){
		switch (input_buffer[0])
		{
			case I2C_REQUEST_ADC0:
				
				adcValTemp=(adcval0>>5);
				output_buffer[0] = (adcValTemp>>8)&0xFF;
				output_buffer[1] = adcValTemp&0xFF;
			break;
			default:
				output_buffer[0]=66;
				output_buffer[1]=66;//input_buffer_length;//input_buffer[0];
			break;
				//output_buffer[1]=-1;
		}
		
		
	}else{
		*output_buffer_length=2;
		output_buffer[0]=88;
		output_buffer[1]=88;
	}
	
	// the data to be returned
	//(0x11);//regs[currentReg];
	
	// send the next reg next time
	//currentReg++;
	//if (currentReg > sizeof(regs)) {
		//currentReg = 0;
	//}
	//return;
	// If you have multiple bytes, return each one:
	//output_buffer[0] = regs[currentReg];
	//output_buffer[1] = regs[currentReg + 1];

	// If you want to send a single value larger than one byte, you will need to split it into bytes,
	// send and then reassemble at the master. Maximum size in the library default is 32 bytes
	// You can increase this in usitwislave.h
	//uint16_t val = 256;
	///*output_buffer_length = 2;
	//output_buffer[0] = (val >> 8) & 0xFF;
	//output_buffer[1] = val & 0xFF;
}

void idle() {
	// whatever you need to do, flash LEDs, etc.
}
/*
void sleep_enable()
{
	MCUCR|=(1<<SM0);      // enabling sleep mode and powerdown sleep mode
	MCUCR|= (1<<SE);     //Enabling sleep enable bit
	//__asm__ __volatile__ ( "sleep" "\n\t" :: ); //Sleep instruction to put controller to sleep
	//controller stops executing instruction after entering sleep mode
}
void sleep_disable(){
	MCUCR&=~(1<<SE);
}*/

int main(void)
{
	DDRB|=(1<<PB6);
	adc_setup();
	timer1_setup();
	usi_twi_slave(DEVICE_ADDRESS, 1, request, ((void*)0));
	sei();
	while (1);
	
}

