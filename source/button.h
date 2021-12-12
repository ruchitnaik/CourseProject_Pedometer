/*
 * button.h
 *
 *  Created on: Dec 11, 2021
 *      Author: Ruchit Naik
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "MKL25Z4.h"
#include "stdbool.h"

/*******************************************************************************
 * Macros for GPIO related configuration
 ******************************************************************************/
#define MASK(x)	(1UL << (x))
#define SW_PIN	5					//Port A, Pin 5

/**
 * @func	switch_Init
 * @brief	Initialized GPIO for a push button interface in input mode with the
 * 			the pull-up resistor functionality enabled. It is initialized to give
 * 			interrupt when pressed. The interrupt transfers the control to IRQ
 * 			Handler for the configured GPIO Port
 * @param	none
 * @return	none
 */
void button_Init(void);

/**
 * @func	get_flagSwitch
 * @brief	Exposes the state of the variable 'flagswitch' to other files
 * 			of the project
 * @param	none
 * @return	flagswitch
 */
bool get_flagSwitch(void);

#endif /* BUTTON_H_ */
