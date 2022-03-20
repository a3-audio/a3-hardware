/*
* init.c
*
* Created: 17/03/2022 12:18:00
*  Author: tirii
*/

#include "init.h"







void button_init(button buttons[]){
	for (int i=0;i<4;i++)
	{
		buttons[i].state=STATE_BUT_RELEASED;
		buttons[i].sample=STATE_BUT_RELEASED;
	}
	
	BITMASK_CLEAR(PORTC.DIR,PIN3_bm);
	BIT_SET(PORTC.PIN3CTRL,PORT_PULLUPEN_bp);//BUtton0 PC3
	BITMASK_CLEAR(PORTA.DIR,PIN4_bm);
	BIT_SET(PORTA.PIN4CTRL,PORT_PULLUPEN_bp);//Button1 PA4

	BITMASK_CLEAR(PORTC.DIR,PIN0_bm);
	BIT_SET(PORTC.PIN0CTRL,PORT_PULLUPEN_bp);//Button2 PC0
	BITMASK_CLEAR(PORTB.DIR,PIN4_bm);
	BIT_SET(PORTB.PIN4CTRL,PORT_PULLUPEN_bp);//Button3 PB4
	_delay_ms(1);
}

void encode_init(int8_t *last,int8_t *enc_delta) {
	int8_t new;
	// init encoder
	BIT_CLEAR(ENC_A_PT.DIR,ENC_A_BP);
	BIT_SET(ENC_A_PT.PIN1CTRL,PORT_PULLUPEN_bp);//Button1 PA4
	BIT_CLEAR(ENC_B_PT.DIR,ENC_B_BP);
	BIT_SET(ENC_B_PT.PIN3CTRL,PORT_PULLUPEN_bp);//Button1 PA4
	//_delay_ms(1);
	
	new = 0;
	if(BIT_CHECK(ENC_A_PT.IN,ENC_A_BP)) new  = 3;
	if(BIT_CHECK(ENC_B_PT.IN,ENC_B_BP)) new ^= 1;       // convert gray to binary
	*last = new;                         // power on state
	*enc_delta = 0;
}



void led_bus_init(){
	BITMASK_SET(LED_SHD_PT.DIR,(1<<LED_SHD_BP)|(1<<LED_SHC_BP));
	BIT_SET(LED_SHU_PT.DIR,LED_SHU_BP);
	SPI0.CTRLA=SPI_MASTER_bm|SPI_PRESC_DIV4_gc;
	SPI0.CTRLB=SPI_BUFEN_bm|SPI_SSD_bm;
	SPI0.CTRLA|=SPI_ENABLE_bm;
}


void i2c_slave_init()
{
	uint8_t addr=8;
	TWI0.SADDR = addr|0x01;				//Slave address & enable general call
	TWI0.SCTRLA = TWI_ENABLE_bm |	    //Enable slave peripheral
	TWI_APIEN_bm |		//Enable address match interrupt
	TWI_PIEN_bm |			//Enable stop interrupt
	TWI_DIEN_bm |			//Enable data interrupt
	TWI_SMEN_bm;			//Enable smart mode
}


void timer0_init(){
	TCA0.SINGLE.PER=1;//255;//&0xFF;
	//TCA0.SINGLE.PERH=(255>>8)&0xFF;
	TCA0.SINGLE.INTCTRL|=TCA_SINGLE_OVF_bm; //enable counter intterrupt on overflow
	TCA0.SINGLE.CTRLA|=TCA_SINGLE_CLKSEL_DIV256_gc|TCA_SINGLE_ENABLE_bm;
}
void timer1_init(){
	TCB0.CCMP=8;
	//TCA0.SINGLE.PERH=(255>>8)&0xFF;
	TCB0.INTCTRL|=TCB_CAPT_bm; //enable counter intterrupt on overflow
	TCB0.CTRLA|=TCB_CLKSEL_TCA0_gc|TCA_SINGLE_ENABLE_bm;
}

/*
Initialize the SPI to a basic functional state by following these steps:
1. Configure the SS pin in the port peripheral.
2. Select SPI master/slave operation by writing the Master/Slave Select bit (MASTER) in the Control A register
(SPIn.CTRLA).
3. In Master mode, select the clock speed by writing the Prescaler bits (PRESC) and the Clock Double bit
(CLK2X) in SPIn.CTRLA.
4. Optional: Select the Data Transfer mode by writing to the MODE bits in the Control B register (SPIn.CTRLB).
5. Optional: Write the Data Order bit (DORD) in SPIn.CTRLA.
6. Optional: Setup Buffer mode by writing BUFEN and BUFWR bits in the Control B register (SPIn.CTRLB).
7. Optional: To disable the multi-master support in Master mode, write ‘1’ to the Slave Select Disable bit (SSD) in
SPIn.CTRLB.
8. Enable the SPI by writing a ‘1’ to the ENABLE bit in SPIn.CTRLA.
*/

