/*
 * tsi.h
 *
 *  Created on: Dec 11, 2021
 *      Author: rtrru
 */

#ifndef TSI_H_
#define TSI_H_

#include <stdbool.h>
#include <stdint.h>
#include "fsl_debug_console.h"



/************************************************
 * TSI Calibrations
 ************************************************/
#define TOUCH_OFFSET		500
#define TOUCH_MIN_THRESHOLD 150

/************************************************
 * Enable debounce feature. Un-comment to enable
 ************************************************/
//#define ENABLE_DEBOUNCE
#define DEBOUNCE_ITERATIONS 10


//TSI Function prototypes

/**
 * @function TSI_Init
 * @brief  	 Initializes the parameters for the capacitive touch sensor
 * @param    none
 * @return   none
 */
void TSI_Init(void);

/**
 * @function TSI_Detect
 * @brief  	 Detect the touch sensor to return if touch is detected or not
 * @param    none
 * @return   bool true 	if touch detected
 * 				  false if touch not detected
 */
bool TSI_Detect(void);

#endif /* TSI_H_ */
