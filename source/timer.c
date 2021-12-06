/*
 * timer.c
 *
 *  Created on: Dec 4, 2021
 *      Author: Ruchit Naik
 */

#include "timer.h"

ticktime_t Ticks;

/**
 * @func	init_systick
 * @brief	Initializes SysTick timer in interrupt mode. Configured to
 * 			to get interrupts at every 1 ms.
 * @param	none
 * @return	none. Generates interrupt in SysTick_Handler() whenever the
 * 			LOAD value is lapsed
 */
void init_systick(void){
	SysTick->LOAD = (48000000/16/1000);				//Interrupt at every 1ms
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;								//Force reloading the counter value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk |		//Enable Systick timer
					SysTick_CTRL_ENABLE_Msk;
	NVIC_EnableIRQ(SysTick_IRQn);					//Enable Systick timer interrupt
}

/**
 * @func	now
 * @brief	Gives the time in sixteenth of a second since the startup
 * @param	none
 * @return	Returns the time since startup
 */
ticktime_t now(){
	return Ticks;									//Returns time since startup
}

/**
 * @func	reset_timer
 * @brief	Reset the counter of SysTick timer to 0
 * @param	none
 * @return	none
 */
void reset_timer(){
	SysTick->VAL = 0;								//Resetting the counter to 0
}

/**
 * @func	get_timer
 * @brief	Returns the current tick form the timer. It gets reset
 * 			on every reset_timer() calls
 * @param	none
 * @return	Current tick from the counter
 */
ticktime_t get_timer(){
	return SysTick->VAL;							//Return current counter
}

/**
 * @func	SysTick_Handler()
 * @brief	Handles the interrupt caused by SysTick timer
 * @param	none
 * @return	none
 */
void SysTick_Handler(){
	Ticks++;				//Increment ticks on each interrupt
}

/**
 * @func	getTicks()
 * @brief	Gives the number of ticks since the boot of the program
 * @param	none
 * @return	ticktime_t	Number of ticks
 */
ticktime_t getTicks(){
	return Ticks;			//Retuns the Ticks counter to the main code
}

/**
 * @func	delay()
 * @brief	gives delay for input amount of msecs.
 * @param	delay_time	time to generate msec delay
 * @return	none
 */
void delay(uint16_t delay_time){
	uint32_t current_time = getTicks();
	while((getTicks() - current_time) <= delay_time){
		__asm volatile ("nop");
	}
}
