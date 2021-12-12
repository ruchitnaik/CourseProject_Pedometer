/*
 * utility.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Ruchit Naik
 */

#include "utility.h"

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


uint16_t detect_step(uint16_t count, int i){
	read_full_xyz();

	total_vect[i] = sqrt(((acc_x - xavg) * (acc_x - xavg)) + ((acc_y - yavg) *
						(acc_y - yavg)) + ((acc_z - zavg) * (acc_z - zavg)));

	total_avg[i] = (total_vect[i] + total_vect[i - 1]) / 2 ;
	printf("Movement val: %d\r\n", total_avg[i]);
	delay(100);
	if(((total_avg[i]>STEP_THRESHOLD)||((total_avg[i]-total_avg[i-1])>STEP_CHANGE_THRESHOLD))
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
