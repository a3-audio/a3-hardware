/*
* button.c
*
* Created: 22/03/2022 15:18:23
*  Author: tirii
*/
#include "button.h"

uint8_t buttons[4];
uint8_t buttonCount=0;
uint8_t buttonStatesNew=0;
uint8_t buttonStates=0;
uint8_t but_getValue(){
	return buttonStates;
}
void but_start(){
	if(BIT_CHECK(BU0_PT.IN,BU0_BP)){
		BIT_CLEAR(buttons[0],buttonCount);
		}else{
		BIT_SET(buttons[0],buttonCount);
	}
	if(buttons[0]==STATE_BUT_RELEASED){
		BIT_CLEAR(buttonStatesNew,BU0_STAT_BP);
	}else
	if(buttons[0]==STATE_BUT_PRESSED){
		BIT_CLEAR(buttonStatesNew,BU0_STAT_BP);
	}
	if(BIT_CHECK(BU1_PT.IN,BU1_BP)){
		BIT_CLEAR(buttons[1],buttonCount);
		}else{
		BIT_SET(buttons[1],buttonCount);
	}
	if(buttons[1]==STATE_BUT_RELEASED){
		BIT_CLEAR(buttonStatesNew,BU1_STAT_BP);
	}else
	if(buttons[1]==STATE_BUT_PRESSED){
		BIT_CLEAR(buttonStatesNew,BU1_STAT_BP);
	}

	if(BIT_CHECK(BU2_PT.IN,BU2_BP)){
		BIT_CLEAR(buttons[2],buttonCount);
		}else{
		BIT_SET(buttons[2],buttonCount);
	}
	if(buttons[2]==STATE_BUT_RELEASED){
		BIT_CLEAR(buttonStatesNew,BU2_STAT_BP);
	}else
	if(buttons[2]==STATE_BUT_PRESSED){
		BIT_CLEAR(buttonStatesNew,BU2_STAT_BP);
	}

	if(BIT_CHECK(BU3_PT.IN,BU3_BP)){
		BIT_CLEAR(buttons[3],buttonCount);
		}else{
		BIT_SET(buttons[3],buttonCount);
	}
	if(buttons[3]==STATE_BUT_RELEASED){
		BIT_CLEAR(buttonStatesNew,BU3_STAT_BP);
	}else
	if(buttons[3]==STATE_BUT_PRESSED){
		BIT_CLEAR(buttonStatesNew,BU3_STAT_BP);
	}
	buttonCount=(buttonCount+1)&0b00000111;
	cli();
	buttonStates=buttonStatesNew;
	sei();
	
}
void but_init(){
	for (int i=0;i<4;i++)
	{
		buttons[i]=STATE_BUT_RELEASED;
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