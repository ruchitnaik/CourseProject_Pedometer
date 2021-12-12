/*
 * button.c
 *
 *  Created on: Dec 11, 2021
 *      Author: Ruchit Naik
 */

#include "button.h"

volatile bool flagSwitch = false;

/**
 * @func	switch_Init
 * @brief	Initialized GPIO for a push button interface in input mode with the
 * 			the pull-up resistor functionality enabled. It is initialized to give
 * 			interrupt when pressed. The interrupt transfers the control to IRQ
 * 			Handler for the configured GPIO Port
 * @param	none
 * @return	none
 */
void button_Init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	PORTA->PCR[SW_PIN] = PORT_PCR_MUX(1) | PORT_PCR_PS_MASK
						| PORT_PCR_PE_MASK | PORT_PCR_IRQC(11);
	//Clear switch bits to input
	PTA->PDDR &= ~MASK(SW_PIN);
	//Configuring NVIC
	NVIC_SetPriority(PORTA_IRQn, 3);
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);

	/* Configure PRIMASK */
	__enable_irq();
}


/**
 * @func	PORTA_IRQHandler
 * @brief	Handles interrupt caused by a pin on PORT A, if it is enabled.
 * 			It receives callback for interrupts caused by any of the pin
 * 			on PORT A.
 * @param	none
 * @return	none
 */
void PORTA_IRQHandler(void){
	if(PORTA->ISFR & MASK(SW_PIN)){
		flagSwitch = false;
		if(!(PTA->PDIR & MASK(SW_PIN))){
			flagSwitch = true;
		}
	}
	PORTA->ISFR = 0xffffffff;
}

/**
 * @func	get_flagSwitch
 * @brief	Exposes the state of the variable 'flagswitch' to other files
 * 			of the project
 * @param	none
 * @return	flagswitch
 */
bool get_flagSwitch(void){
	return flagSwitch;
}
