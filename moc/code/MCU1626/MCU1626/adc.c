/*
 * adc.c
 *
 * Created: 20/03/2022 22:54:00
 *  Author: tirii
 */ 
/*
The following steps are recommended to initialize and run the ADC in basic operation:
1. Enable the ADC by writing a ‘1’ to the ENABLE bit in the Control A (ADCn.CTRLA) register.
2. Configure the Prescaler (PRESC) bit field in the Control B (ADCn.CTRLB) register.
3. Configure the Timebase (TIMEBASE) and Reference Select (REFSEL) bit fields in the Control C
(ADCn.CTRLC) register.
4. Configure the Sample Duration (SAMPDUR) bit field in the Control E (ADCn.CTRLE) register.
5. Optional: Configure the number of samples to be accumulated by writing the Sample Accumulation Number
Select (SAMPNUM) bit field in the Control F (ADCn.CTRLF) register.
6. Optional: Enable the Free-Running mode by writing a ‘1’ to the Free-Running (FREERUN) bit in the Control F
register.
7. Configure a positive input by writing to the MUXPOS bit field in the Positive Input Multiplexer
(ADCn.MUXPOS) register.
8. Optional: Configure a negative input by writing to the MUXNEG bit field in the Negative Input Multiplexer
(ADCn.MUXNEG) register.
9. Optional: Select Differential ADC conversion by writing a ‘1’ to the Differential (DIFF) bit in the Command
(ADCn.COMMAND) register.
10. Configure the mode of operation for the ADC by writing to the MODE bit field in the Command register.
11. Configure how an ADC conversion will start by writing to the START bit field in the Command register. If the
IMMEDIATE command is written, a conversion will start immediately.
12. Wait until the Result Ready (RESRDY) bit in the Interrupt
*/
void adc_init(){
	ADC0.CTRLA|=ADC_ENABLE_bm|ADC_LOWLAT_bm;
	ADC0.CTRLB|=ADC_PRESC_DIV2_gc;
	ADC0.CTRLC|=(ADC_TIMEBASE<< ADC_TIMEBASE_gp)|ADC_REFSEL_VDD_gc;
	ADC0.CTRLE|=3;	//The simplest way of finding a good value is to do some quick single samples, store the results,
	//and see if the first sample(s) deviate too much from the others. If it does, then the SAMPDUR is too short.
	//For this to work, the input signal needs to be fairly stable while sampling.
	ADC0.COMMAND|=ADC_MODE_SINGLE_12BIT_gc;
	ADC0.INTCTRL|=ADC_SAMPRDY_bm;
}