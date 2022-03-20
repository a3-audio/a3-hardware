/*
 * colormath.c
 *
 * Created: 16/03/2022 13:14:21
 *  Author: tirii
 */ 

#include "ledandcolor.h"

uint8_t iLed_event=0;
rgbLed rgbButtons[4];
led leds[12];
ledEvent led_events[12];
uint8_t nLed_event=0;

ledEvent getNextLedEvent(){
		iLed_event%=nLed_event;
		ledEvent retVal=led_events[iLed_event];
		iLed_event++;
		return retVal;
}
void updateRGBLed(uint8_t number,uint16_t angle,uint8_t value){
	hsvtoRGB (&rgbButtons[number],(float)angle, value);
	updateColorSystem(rgbButtons[number],leds,led_events,&nLed_event);
}
int ledCompare(const void *a, const void *b){
	
	led *a1=(led *)a;
	led *a2=(led *)b;
	return a1->time - a2->time;
}
void	hsvtoRGB (rgbLed *rgbBut,float angle, uint8_t val)
{
	float fAngle=angle*0.0167;

	uint8_t c[3];
	if (angle < 60)
	{
		float x2 = val *fAngle;
		
		c[0]=val;c[1]=x2;c[2]=0;
	}
	else if (angle < 120)
	{
		float x2 = val * (2 - fAngle);
		c[0]=x2;c[1]=val;c[2]=0;
	}
	else if (angle < 180)
	{
		float x2 = val * (fAngle-2);
		c[0]=0;c[1]=val;c[2]=x2;
	}
	else if (angle == 180)
	{
		c[0]=0;c[1]=0;c[2]=val;
	}else if (angle < 240)
	{
		float x2 = val * (3 - fAngle);
		c[0]=0;c[1]=x2;c[2]=val;
	}
	else if (angle < 300)
	{
		float x2 = val * (fAngle-4);
		c[0]=x2;c[1]=0;c[2]=val;
	}else  if (angle == 360)
	{
		c[0]=val;c[1]=0;c[2]=0;
		}else    {
		float x2 = val * (6 - fAngle);
		c[0]=val;c[1]=0;c[2]=x2;
	}
	rgbBut->red.time=c[0];
	rgbBut->green.time=c[1];
	rgbBut->blue.time=c[2];
}
void rgb_led_init(){
	rgbButtons[0].red.position=POS_LEDS1R;
	leds[0].position=POS_LEDS1R;
	rgbButtons[0].green.position=POS_LEDS1G;
	leds[1].position=POS_LEDS1G;
	rgbButtons[0].blue.position=POS_LEDS1B;
	leds[2].position=POS_LEDS1B;
	
	rgbButtons[1].red.position=POS_LEDS2R;
	leds[3].position=POS_LEDS2R;
	rgbButtons[1].green.position=POS_LEDS2G;
	leds[4].position=POS_LEDS2G;
	rgbButtons[1].blue.position=POS_LEDS2B;
	leds[5].position=POS_LEDS2B;
	
	rgbButtons[2].red.position=POS_LEDS3R;
	leds[6].position=POS_LEDS3R;
	rgbButtons[2].green.position=POS_LEDS3G;
	leds[7].position=POS_LEDS3G;
	rgbButtons[2].blue.position=POS_LEDS3B;
	leds[8].position=POS_LEDS3B;
	
	rgbButtons[3].red.position=POS_LEDS4R;
	leds[9].position=POS_LEDS4R;
	rgbButtons[3].green.position=POS_LEDS4G;
	leds[10].position=POS_LEDS4G;
	rgbButtons[3].blue.position=POS_LEDS4B;
	leds[11].position=POS_LEDS4B;
}

//http://alienryderflex.com/quicksort/
void updateColorSystem(rgbLed rgbBut,led fLed[],ledEvent fLedEvents[],uint8_t *fNLedEvents){

	//exchange values in led array
	for (int i=0;i<12;i++)
	{
		if(rgbBut.red.position==fLed[i].position){
			fLed[i].time=rgbBut.red.time;
			}else if(rgbBut.green.position==fLed[i].position){
			fLed[i].time=rgbBut.green.time;
			}else if(rgbBut.blue.position==fLed[i].position){
			fLed[i].time=rgbBut.blue.time;
		}
	}
	qsort(fLed,12,sizeof(led),ledCompare);
	uint16_t shift=0xFFFF;
	BIT_CLEAR(shift,fLed[0].position);
	fLedEvents[0].time=0;
	fLedEvents[0].shiftVal=shift;
	uint8_t nLed_event=0;
	for(int i=1;i<12&&fLed[i].time<255;i++){
		if(fLed[i].time>fLedEvents[nLed_event].time){
			nLed_event++;
			fLedEvents[nLed_event].time=fLed[i].time;
		}
		BIT_CLEAR(shift,fLed[i].position);
		fLedEvents[nLed_event].shiftVal=shift;
	}
	nLed_event++;
	#ifdef ECLIPSE_DEBUG
	for(int i=0;i<nLed_event;i++){
		printf("%d	%04X\n",fLedEvents[i].time,fLedEvents[i].shiftVal);
	}
	#endif
	uint8_t lastTime=0;
	if(nLed_event>1){
		for(int i=0;i<nLed_event;i++){
			if(i==(nLed_event-1))
			fLedEvents[i].time=255-lastTime;
			else
			fLedEvents[i].time=fLedEvents[i+1].time-lastTime;
			lastTime+=fLedEvents[i].time;
		}
		}else{
		fLedEvents[0].time=255;
	}
	#ifdef ECLIPSE_DEBUG
	for(int i=0;i<nLed_event;i++){
		printf("%d	%04X\n",fLedEvents[i].time,fLedEvents[i].shiftVal);
	}
	#endif
	*fNLedEvents=nLed_event;
}
