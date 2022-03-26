/*
 * colormath.c
 *
 * Created: 16/03/2022 13:14:21
 *  Author: tirii
 */

#include "ledandcolor.h"

uint8_t iLedEvent = 0;
rgbLed rgbButtons[4];
ledStruct leds[12];
ledEvent ledEventsUpdate[12];
ledEvent *ptrLedEvents=NULL;
ledEvent ledEvents[12];
uint8_t nLedEventUpdate = 1;
uint8_t nLedEvent = 1;

void led_shiftSend(uint16_t data) {
	if (SPI0.INTFLAGS & SPI_DREIF_bm) {			//transfer complete flag
		SPI0.INTCTRL = SPI_TXCIE_bm;
		SPI0.DATA = (uint8_t) ((data >> 8) & 0xFF);
		SPI0.DATA = (uint8_t) data;
	}
}
void led_init() {
	BITMASK_SET(LED_SHD_PT.DIR, (1<<LED_SHD_BP)|(1<<LED_SHC_BP));
	BIT_SET(LED_SHU_PT.DIR, LED_SHU_BP);
	SPI0.CTRLA = SPI_MASTER_bm | SPI_PRESC_DIV4_gc;
	SPI0.CTRLB = SPI_BUFEN_bm | SPI_SSD_bm;
	SPI0.CTRLA |= SPI_ENABLE_bm;
	led_rgbInit();
	led_updateRGB(0,0,0);
	led_updateRGB(1,0,0);
	led_updateRGB(2,0,0);
	led_updateRGB(3,0,0);
}
ledEvent led_getNextEvent() {

	if(ptrLedEvents&&iLedEvent==0){
		memcpy(ledEvents,ledEventsUpdate,sizeof ledEvents[0]*nLedEventUpdate);
		nLedEvent=nLedEventUpdate;
		ptrLedEvents=NULL;
	}
	ledEvent retVal = ledEvents[iLedEvent];
	iLedEvent++;
	iLedEvent %= nLedEvent;
	return retVal;
}
void led_updateRGB(uint8_t number, uint16_t angle, uint8_t value) {
	led_hsvToRGB(&rgbButtons[number], (float) angle, value);
	led_updateColorSystem();
	//We have a new version for our shift register
	ptrLedEvents=ledEventsUpdate;
}
int led_Compare(const void *a, const void *b) {

	ledStruct *a1 = (ledStruct*) a;
	ledStruct *a2 = (ledStruct*) b;
	return a1->ledVal.time - a2->ledVal.time;
}
void led_hsvToRGB(rgbLed *rgbBut, float angle, uint8_t val) {
	float fAngle = angle * 0.016667;

	uint8_t c[3];
	if (angle < 60) {//max1
		float x2 = val * fAngle;

		c[0] = val;
		c[1] = x2;
		c[2] = 0;
		} else if (angle < 120) {
		float x2 = val * (2 - fAngle);//max 2
		c[0] = x2;
		c[1] = val;
		c[2] = 0;
		} else if (angle < 180) {
		float x2 = val * (fAngle - 2);//max 3
		c[0] = 0;
		c[1] = val;
		c[2] = x2;
		} else if (angle < 240) {
		float x2 = val * (4 - fAngle);//max 4
		c[0] = 0;
		c[1] = x2;
		c[2] = val;
		} else if (angle < 300) {
		float x2 = val * (fAngle - 4); //max 5
		c[0] = x2;
		c[1] = 0;
		c[2] = val;
		} else {
		float x2 = val * (6 - fAngle);//max 6
		c[0] = val;
		c[1] = 0;
		c[2] = x2;
	}
	rgbBut->red.time = c[0];
	rgbBut->green.time = c[1];
	rgbBut->blue.time = c[2];
}
void led_rgbInit() {
	rgbButtons[0].red.position = POS_LEDS1R;
	leds[0].ledVal.position = POS_LEDS1R;
	leds[0].newTime=&(rgbButtons[0].red.time);
	rgbButtons[0].green.position = POS_LEDS1G;
	leds[1].ledVal.position = POS_LEDS1G;
	leds[1].newTime=&(rgbButtons[0].green.time);
	rgbButtons[0].blue.position = POS_LEDS1B;
	leds[2].ledVal.position = POS_LEDS1B;
	leds[2].newTime=&(rgbButtons[0].blue.time);

	rgbButtons[1].red.position = POS_LEDS2R;
	leds[3].ledVal.position = POS_LEDS2R;
	leds[3].newTime=&(rgbButtons[1].red.time);
	rgbButtons[1].green.position = POS_LEDS2G;
	leds[4].ledVal.position = POS_LEDS2G;
	leds[4].newTime=&(rgbButtons[1].green.time);
	rgbButtons[1].blue.position = POS_LEDS2B;
	leds[5].ledVal.position = POS_LEDS2B;
	leds[5].newTime=&(rgbButtons[1].blue.time);

	rgbButtons[2].red.position = POS_LEDS3R;
	leds[6].ledVal.position = POS_LEDS3R;
	leds[6].newTime=&(rgbButtons[2].red.time);
	rgbButtons[2].green.position = POS_LEDS3G;
	leds[7].ledVal.position = POS_LEDS3G;
	leds[7].newTime=&(rgbButtons[2].green.time);
	rgbButtons[2].blue.position = POS_LEDS3B;
	leds[8].ledVal.position = POS_LEDS3B;
	leds[8].newTime=&(rgbButtons[2].blue.time);

	rgbButtons[3].red.position = POS_LEDS4R;
	leds[9].ledVal.position = POS_LEDS4R;
	leds[9].newTime=&(rgbButtons[3].red.time);
	rgbButtons[3].green.position = POS_LEDS4G;
	leds[10].ledVal.position = POS_LEDS4G;
	leds[10].newTime=&(rgbButtons[3].green.time);
	rgbButtons[3].blue.position = POS_LEDS4B;
	leds[11].ledVal.position = POS_LEDS4B;
	leds[11].newTime=&(rgbButtons[3].blue.time);


	ledEventsUpdate[0].shiftVal=0;
	ledEventsUpdate[0].time=0;
}

//http://alienryderflex.com/quicksort/
void led_updateColorSystem() {
	//exchange values in led array
	for (int i = 0; i < 12; i++) {
		//the l
		leds[i].ledVal.time=*leds[i].newTime;
	}
	//sort the leds by their time value
	qsort(leds, 12, sizeof(ledStruct), led_Compare);
	uint16_t shift = 0b1110011111100111;
	nLedEventUpdate = 0;
	ledEventsUpdate[0].time=0;
	//combining time events to shift values
	//it's smaller then 255 because 255 is full on already
	for (int i = 0; i < 12 && leds[i].ledVal.time < 255; i++) {
		if (leds[i].ledVal.time > ledEventsUpdate[nLedEventUpdate].time) {
			//we have a new time event
			nLedEventUpdate++;
			ledEventsUpdate[nLedEventUpdate].time = leds[i].ledVal.time;
		}
		//if bit is cleared led will be switched off at this time
		BIT_CLEAR(shift, leds[i].ledVal.position);
		ledEventsUpdate[nLedEventUpdate].shiftVal = shift;
	}
	nLedEventUpdate++;
#ifdef ECLIPSE_DEBUG
	for (int i = 0; i < nLedEventUpdate; i++) {
		printf("%d	%04X\n", ledEventsUpdate[i].time, ledEventsUpdate[i].shiftVal);
	}
#endif

	//building the delta between send events
	uint8_t lastTime = 0;
		for (int i = 0; i < nLedEventUpdate; i++) {
			//the last event is untill 255
			if (i == (nLedEventUpdate - 1))
				ledEventsUpdate[i].time = 255 - lastTime;
			else
				ledEventsUpdate[i].time = ledEventsUpdate[i + 1].time - lastTime;
			lastTime += ledEventsUpdate[i].time;
		}
#ifdef ECLIPSE_DEBUG
	for (int i = 0; i < nLedEventUpdate; i++) {
		printf("%d	%04X\n", ledEventsUpdate[i].time, ledEventsUpdate[i].shiftVal);
	}
#endif
}
