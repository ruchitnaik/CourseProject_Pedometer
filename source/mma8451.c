/*
 * mma8451.c
 *
 *  Created on: Dec 4, 2021
 *      Author: Ruchit Naik
 */

#include "mma8451.h"

int16_t acc_x=0, acc_y=0, acc_z=0;

/**
 * @function init_mma
 * @brief  	 Initialize accelerometer by writing the register
 * 			 control register as 0x01.
 * @param    none
 * @return   none
 */
int init_mma(void){
	//Set active mode, 14 bit samples and 800hz ODR
	I2C0_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/**
 * @function read_full_xyz
 * @brief  	 Read acceleration measure for all the 3-axis
 * 			 together.
 * @param    none
 * @return   none
 */
void read_full_xyz(void){
	int i;
	uint8_t data[6];
	int16_t temp[3];

	I2C0_start();
	I2C0_read_setup(MMA_ADDR, REG_XHI);

	//Read five bytes in repeated mode
	for(i=0; i<5; i++){
		data[i] = I2C0_repeated_read(0);
	}
	//Read last byte ending repeated mode
	data[i] = I2C0_repeated_read(1);

	for(i=0; i<3; i++){
		temp[i] = (int16_t)((data[2*i]<<8) | data[2*i+1]);
	}

	//Align for 14 bits
	acc_x = temp[0]/4;
	acc_y = temp[1]/4;
	acc_z = temp[2]/4;

//	printf("X: %d | Y: %d | Z: %d\r\n", acc_x, acc_y, acc_z);
}

/**
 * @function read_xyz
 * @brief  	 Read the register where the x, y and z-axis values
 * 			 are stored.
 * @param    none
 * @return   none
 */
void read_xyz(void){
	acc_x = (int8_t)I2C0_read_byte(MMA_ADDR, REG_XHI);
	//100ms delay
	delay(100);
	acc_y = (int8_t)I2C0_read_byte(MMA_ADDR, REG_YHI);
	//100ms delay
	delay(100);
	acc_z = (int8_t)I2C0_read_byte(MMA_ADDR, REG_ZHI);
}

/**
 * @function calibrate
 * @brief  	 Calibrates the reading of the accelerometer. The
 * 			 function stores the value clearing the offset. It
 * 			 returns the average values for all 3 axis to a
 * 			 dedicated buffer.
 * @param    xval[in]	pointer to buffer to store 100 values of
 * 						x-axis.
 * 			 yval[in]	pointer to buffer to store 100 values of
 * 						y-axis.
 * 			 zval[in]	pointer to buffer to store 100 values of
 * 						z-axis.
 * 			 xavg[out]	returns the average of acc. along x-axis
 * 			 yavg[out]	returns the average of acc. along y-axis
 * 			 zavg[out]	returns the average of acc. along z-axis
 * @return   average values of acceleration along all the 3 axis
 */
void calibrate(int16_t *xval, int16_t *yval, int16_t *zval, int *xavg, int *yavg, int *zavg){
	int sum = 0, sum1 = 0, sum2 = 0;
	for(int i = 0; i<100; i++){
		read_full_xyz();
		xval[i] = acc_x;
		sum = xval[i] + sum;

		yval[i] = acc_y;
		sum1 = yval[i] + sum1;

		zval[i] = acc_z;
		sum2 = zval[i] + sum2;
	}
	delay(100);
	*xavg = sum/100;
#ifdef DEBUG
	printf("avg X: %d\r\n", *xavg);
#endif

	*yavg = sum1/100;
#ifdef DEBUG
	printf("avg Y: %d\r\n", *yavg);
#endif

	*zavg = sum2/100;
#ifdef DEBUG
	printf("avg Z: %d\r\n", *zavg);
#endif
}
