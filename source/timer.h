/*
 * timer.h
 *
 *  Created on: Dec 4, 2021
 *      Author: Ruchit Naik
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include "MKL25Z4.h"

typedef uint32_t ticktime_t;

/**
 * @func	init_systick
 * @brief	Initializes SysTick timer in interrupt mode. Configured to
 * 			to get interrupts at every 1 ms.
 * @param	none
 * @return	none. Generates interrupt in SysTick_Handler() whenever the
 * 			LOAD value is lapsed
 */
void init_systick(void);

/**
 * @func	now
 * @brief	Gives the time in sixteenth of a second since the startup
 * @param	none
 * @return	Returns the time since startup
 */
ticktime_t now();

/**
 * @func	reset_timer
 * @brief	Reset the counter of SysTick timer to 0
 * @param	none
 * @return	none
 */
void reset_timer();

/**
 * @func	get_timer
 * @brief	Returns the current tick form the timer. It gets reset
 * 			on every reset_timer() calls
 * @param	none
 * @return	Current tick from the counter
 */
ticktime_t get_timer();

/**
 * @func	getTicks()
 * @brief	Gives the number of ticks since the boot of the program
 * @param	none
 * @return	ticktime_t	Number of ticks
 */
ticktime_t getTicks();

/**
 * @func	delay()
 * @brief	gives delay for input amount of msecs.
 * @param	delay_time	time to generate msec delay
 * @return	none
 */
void delay(uint16_t delay_time);

#endif /* TIMER_H_ */
