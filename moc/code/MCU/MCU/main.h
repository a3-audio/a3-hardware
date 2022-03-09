/*
 * main.h
 *
 * Created: 24/01/2022 14:38:25
 *  Author: tirii
 */ 


#ifndef MAIN_H_
#define MAIN_H_

//#define __AVR_ATtiny861__


void writeSPI4(uint8_t data);
void rgb_out();

//void sleep_disable();
//void sleep_enable();

void i2c_ack();
void i2c_stop();
void i2c_send_data(uint8_t *tosend,uint8_t nBytes);
void i2c_start(uint8_t device);
void i2c_transfer();
void i2c_setup();




uint8_t rgb_r[]={0,3,3,3,3,3,2,1,0,0,0,0,0,0,0,1,2,3,3,3};
uint8_t rgb_g[]={0,3,0,1,2,3,3,3,3,3,3,3,2,1,0,0,0,0,0,0};
uint8_t rgb_b[]={0,3,0,0,0,0,0,0,0,1,2,3,3,3,3,3,3,3,2,1};



#endif /* MAIN_H_ */