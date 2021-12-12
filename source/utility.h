/*
 * utility.h
 *
 *  Created on: Dec 6, 2021
 *      Author: Ruchit Naik
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdbool.h>
#include <math.h>
#include "mma8451.h"
#include "timer.h"
#include "i2c.h"

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
uint16_t detect_step(uint16_t count, int i);

#endif /* UTILITY_H_ */
