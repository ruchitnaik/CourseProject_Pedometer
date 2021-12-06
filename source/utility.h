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

uint16_t detect_step(uint16_t count, int i);

#endif /* UTILITY_H_ */
