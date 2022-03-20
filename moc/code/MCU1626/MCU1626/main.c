/*
* MCU1626.c
*
* Created: 23/02/2022 13:06:16
* Author : tirii
*/
#include "main.h"





/*
(MALE)
1	 2	 3	 4	 5
GND	SDC	SDA	UPD	VCW
--- PB0	PB1

10	 9	 8	 7	 6	 4	 3	 2
SDA	SHU	ENB	BU3	AD1	AD0	ESW	BU1
PB1	PB2	PB3	PB4	PB5	PA6	PA5	PA4



11	 12	 13	 15	 16	 17	 19		 1	 2	 3
SCL	BU2	ENA	BU0	UPD	SHD	SHC		VCW	UPD	GND
PB0	PC0	PC1	PC3	PA0	PA1	PA3
*/
#define MYAD0	8
#define MYAD1	9


#define SHC	3
#define SHD	1
#define SHU	2

uint8_t nnn=0;
volatile uint8_t twitest=0;
volatile uint8_t spisend[2]={0b11100111,0b01010101};

volatile uint16_t event_led=(1<<EVENT_LEDS1B)|(1<<EVENT_LEDS1R)|(1<<EVENT_COUNTER_OVERFLOW);

uint16_t	event_button=0;
button buttons[4];
uint8_t buttonCount=0;
volatile uint8_t tes[2]={2,77};
volatile uint8_t iTes=0;

volatile uint16_t adcRes[2];

volatile uint8_t counter=0;

int8_t enc_delta;          // -128 ... 127
int16_t encoder_val=0;
static int8_t last;
volatile uint8_t tCounter=0;

//converts an angle and a intensity value to RGB
//angle is 0-360 and val 0-255


ISR(ADC0_SAMPRDY_vect){
	uint8_t tH1=ADC0.INTFLAGS;
	uint8_t tL=ADC0_SAMPLEL;
	uint8_t tH=ADC0_SAMPLEH;
	ADC0.INTFLAGS|=ADC_RESOVR_bm;
	adcRes[0]=((uint16_t)(tH<<8))|tL;
}


ISR(SPI0_INT_vect){
	if(SPI0.INTFLAGS&SPI_TXCIF_bm){
		BIT_SET(LED_SHU_PT.OUTSET,LED_SHU_BP);//ACK BIT ON
		BITMASK_SET(SPI0.INTFLAGS,SPI_TXCIF_bm);
		BITMASK_CLEAR(SPI0.INTCTRL,SPI_TXCIE_bm);
		BIT_SET(event_led,EVENT_LED_ACK_ON);

	
	}
}


ISR(TCA0_OVF_vect){
	BIT_SET(LED_SHU_PT.OUTCLR,LED_SHU_BP);//ACK BIT OFF
	TCA0.SINGLE.INTFLAGS|=TCA_SINGLE_OVF_bm;//clear interrupt flag
	ledEvent rgbEvent=getNextLedEvent();
	TCA0.SINGLE.PER=rgbEvent.time;
	led_shift_send(rgbEvent.shiftVal);
	toggleDebugESW();
}

ISR(TCB0_INT_vect){
	TCB0.INTFLAGS|=TCB_CAPT_bm;
	tCounter++;
}
ISR(TWI0_TWIS_vect)
{
	if(TWI0.SSTATUS & TWI_APIF_bm)					//Address match/stop interrupt
	{
		if (TWI0.SSTATUS & TWI_COLL_bm)
		{
			TWI0.SSTATUS |= TWI_COLL_bm;			//Clear Collision flag
			TWI0_SCTRLB = TWI_SCMD_COMPTRANS_gc;	//complete transaction
			return;
		}
		if(TWI0.SSTATUS & TWI_AP_bm)
		TWI0_SCTRLB = TWI_SCMD_RESPONSE_gc;		//Send ACK after address match
		else
		TWI0_SCTRLB = TWI_SCMD_COMPTRANS_gc;	//complete transaction after Stop
	}
	
	if(TWI0.SSTATUS & TWI_DIF_bm)					//Data interrupt
	{
		if(TWI0.SSTATUS & TWI_DIR_bm)
		{
			TWI0.SDATA = ++nnn;						//Transmit data for Master to read
			
			TWI0_SCTRLB = TWI_SCMD_RESPONSE_gc;
		}
		else
		{
			TWI0_SCTRLB = TWI_SCMD_RESPONSE_gc;
			nnn = TWI0.SDATA;						//Receive data written by Master
		}
	}
}



void led_shift_send(uint16_t data){
	if(SPI0.INTFLAGS&SPI_DREIF_bm){			//transfer complete flag
		SPI0.INTCTRL=SPI_TXCIE_bm;
		BIT_SET(event_led,EVENT_LED_SENDING);
		SPI0.DATA=(uint8_t)((data>>8)&0xFF);
		SPI0.DATA=(uint8_t)data;
	}
}


void adc_start(uint8_t channel){
	if(channel == MYAD0 || channel == MYAD1){
		ADC0.MUXPOS|=channel;
		_delay_us(10);
		ADC0.COMMAND|=ADC_START_IMMEDIATE_gc;
	}
}




uint16_t it=0;
uint16_t tLed0Count=0;//xxx
int main(void)
{	ccp_write_io((void *) & (CLKCTRL.MCLKCTRLB), 0); //protected write to disable prescaler of CPU clock
	debug_init();
	timer0_init();
	timer1_init();
	//i2c_slave_init();
	led_bus_init();
	rgb_led_init();
	updateRGBLed(0,0,255);
	updateRGBLed(1,120,255);
	updateRGBLed(2,240,255);
	updateRGBLed(3,0,255);
	//button_init();
	//adc_init();
	//button_init();
	encode_init(&last,&enc_delta);
	//BITMASK_CLEAR(PORTB.DIR,(PIN1_bm|PIN0_bm));
	sei();
	
	while (1)
	{
		
		//_delay_ms(100);
		//ledshift=0;
		//ledshift=1<<POS_LEDS1B;
		//led_shift_send(ledshift);
		// timer gibt die clock vor
		// clock wird immer erst am Anfang der while schleife erneuert
		// reihenfolge der aufrufe gibt prioietät
		//	timer step 3ms/255
		//	adc startet ergebnis durch interrupt
		//	bool values geben vor ob led aenderung schon gesendet wurde
		
		
		//tCounter=TCA0.SINGLE.CNTL;
		it++;
		it%=360;
		updateRGBLed(0,(it)%360,255);
		updateRGBLed(1,(it+120)%360,255);
		updateRGBLed(2,(it+180)%360,255);
		updateRGBLed(3,(it+240)%360,255);
		_delay_ms(10);
		if(counter!=tCounter){
			
			counter=tCounter;

			if(counter==0){
				
			}
			

		
						
			/*
			if(counter==0||counter==64||counter==128||counter==192){
			if(BIT_CHECK(PORTC.IN,PIN3_bp)){
			BIT_CLEAR(buttons[0].sample,buttonCount);
			}else{
			BIT_SET(buttons[0].sample,buttonCount);
			}
			if(buttons[0].state==STATE_BUT_PRESSED&&buttons[0].sample==STATE_BUT_RELEASED){
			buttons[0].state=STATE_BUT_RELEASED;
			leds[0]=hsvtoRGB(tLed0Count,255);
			}else
			if(buttons[0].state==STATE_BUT_RELEASED&&buttons[0].sample==STATE_BUT_PRESSED){
			buttons[0].state=STATE_BUT_PRESSED;
			tLed0Count+=10;
			tLed0Count%=360;
			leds[0]=hsvtoRGB(100,255);
			}
			
			//... andere buttons
			buttonCount=(buttonCount+1)&0b00000111;
			}else*/
			
			if(counter==32||counter==117||counter==203){
				int8_t new, diff;
				new = 0;
				if(BIT_CHECK(ENC_A_PT.IN,ENC_A_BP)) new  = 3;
				if(BIT_CHECK(ENC_B_PT.IN,ENC_B_BP)) new ^= 1;       // convert gray to binary
				diff = last - new;               // difference last - new
				if( diff & 1 ) {                 // bit 0 = value (1)
					last = new;                    // store new as next last
					enc_delta += (diff & 2) - 1;   // bit 1 = direction (+/-)
				}
				if(enc_delta!=0){
					toggleDebugBU0();
					encoder_val += (enc_delta);          // read a single step encoder
					
					if(encoder_val>360){
						encoder_val-=360;
					}else if (encoder_val<0){
						encoder_val=360-encoder_val;
					}
					//leds[0]=hsvtoRGB(encoder_val,255);
					
					enc_delta=0;
					
				}
			}
			
			/*else{
			
			
			
			enc_delta=0;
			if(encoder_val!=tLed0Count){
			tLed0Count+=10;
			encoder_val=tLed0Count;
			leds[0]=hsvtoRGB(tLed0Count,255);
			
			
			
			}
			}*/
			
			
		}
		
	}
}

