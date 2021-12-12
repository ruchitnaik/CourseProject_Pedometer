/*
 * mma8451.h
 *
 *  Created on: Dec 4, 2021
 *      Author: Ruchit Naik
 */

#ifndef MMA8451_H_
#define MMA8451_H_

#include <stdint.h>
#include <stdio.h>
#include "MKL25Z4.h"
#include "mma8451.h"
#include "timer.h"
#include "i2c.h"

/************************************************
 * MMA8451 registration configuration
 ************************************************/
#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D

#define WHOAMI 0x1A

/**
 * @function init_mma
 * @brief  	 Initialize accelerometer by writing the register
 * 			 control register as 0x01.
 * @param    none
 * @return   none
 */
int init_mma(void);

/**
 * @function read_full_xyz
 * @brief  	 Read acceleration measure for all the 3-axis
 * 			 together.
 * @param    none
 * @return   none
 */
void read_full_xyz(void);

/**
 * @function read_xyz
 * @brief  	 Read the register where the x, y and z-axis values
 * 			 are stored.
 * @param    none
 * @return   none
 */
void read_xyz(void);

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
void calibrate(int16_t *xval, int16_t *yval, int16_t *zval, int *xavg, int *yavg, int *zavg);

#endif /* MMA8451_H_ */
