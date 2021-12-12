/*
 * utility.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Ruchit Naik
 */

#include "utility.h"

/************************************************
 * Step Detection Sensitivity Setting
 ************************************************/
#define	STEP_THRESHOLD			2500
#define STEP_CHANGE_THRESHOLD	750

extern int16_t xval[100];
extern int16_t yval[100];
extern int16_t zval[100];
extern int16_t total_vect[100];
extern int16_t total_avg[100];
extern int xavg, yavg, zavg;
bool step_flag = false;

extern int16_t acc_x, acc_y, acc_z;

/**
 * @function detect_step
 * @brief  	 It implements the step detection algorithm based on
 * 			 the readings of the MMA8451 accelerometer. It checks
 * 			 the resultant acceleration of along all the 3 axis
 * 			 and a 2 state state-machine to decide if step is taken
 * 			 or not.
 * @param    count[in]	previous step count to increment if step is
 * 						taken
 * 			 i[in]		index for the buffer where the new calibrated
 * 			 			acceleration is to be stored based on which
 * 			 			the calculations are done.
 * @return   count		It determines the new step count in case if
 * 						step is taken or not.
 */
uint16_t detect_step(uint16_t count, int i){
	read_full_xyz();

	total_vect[i] = sqrt(((acc_x - xavg) * (acc_x - xavg)) + ((acc_y - yavg) *
						(acc_y - yavg)) + ((acc_z - zavg) * (acc_z - zavg)));

	total_avg[i] = (total_vect[i] + total_vect[i - 1]) / 2 ;
	printf("Movement val: %d\r\n", total_avg[i]);
	delay(100);
	if(((total_avg[i]>STEP_THRESHOLD)/*||((total_avg[i]-total_avg[i-1])>STEP_CHANGE_THRESHOLD)*/)
			&& (step_flag == false)){
		count++;
		step_flag = true;
	}
	else if((total_avg[i] > STEP_THRESHOLD) && (step_flag == true)){
		//Don't count
		__asm volatile ("nop");
	}

	if((((total_avg[i] - total_avg[i-1]) > STEP_CHANGE_THRESHOLD)||
		((total_avg[i-1] - total_avg[i]) > STEP_CHANGE_THRESHOLD)) && (step_flag == true)){
		step_flag = false;
	}
	return count;
}
