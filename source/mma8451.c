/*
 * mma8451.c
 *
 *  Created on: Dec 4, 2021
 *      Author: Ruchit Naik
 */

#include "mma8451.h"

int16_t acc_x=0, acc_y=0, acc_z=0;

int init_mma(void){
	//Set active mode, 14 bit samples and 800hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}


void read_full_xyz(void){
	int i;
	uint8_t data[6];
	int16_t temp[3];

	i2c_start();
	i2c_read_setup(MMA_ADDR, REG_XHI);

	//Read five bytes in repeated mode
	for(i=0; i<5; i++){
		data[i] = i2c_repeated_read(0);
	}
	//Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for(i=0; i<3; i++){
		temp[i] = (int16_t)((data[2*i]<<8) | data[2*i+1]);
	}

	//Align for 14 bits
	acc_x = temp[0]/4;
	acc_y = temp[1]/4;
	acc_z = temp[2]/4;

	printf("X: %d | Y: %d | Z: %d\r\n", acc_x, acc_y, acc_z);
}


void read_xyz(void){
	acc_x = (int8_t)i2c_read_byte(MMA_ADDR, REG_XHI);
	//100ms delay
	delay(100);
	acc_y = (int8_t)i2c_read_byte(MMA_ADDR, REG_YHI);
	//100ms delay
	delay(100);
	acc_z = (int8_t)i2c_read_byte(MMA_ADDR, REG_ZHI);
}
