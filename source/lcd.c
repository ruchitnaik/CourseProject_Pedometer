/*
 * lcd.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Ruchit Naik
 */

#include "lcd.h"

void lcd_init(void){
	//Enable clock to PORTC
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);

	//Enable and initialize all the GPIO pins
	PORTC->PCR[10] |= PORT_PCR_MUX(1);			//Configure PTC10
	PORTC->PCR[7] |= PORT_PCR_MUX(1);			//Configure PTC7
	PORTC->PCR[6] |= PORT_PCR_MUX(1);			//Configure PTC6
	PORTC->PCR[5] |= PORT_PCR_MUX(1);			//Configure PTC5
	PORTC->PCR[4] |= PORT_PCR_MUX(1);			//Configure PTC4
	PORTC->PCR[3] |= PORT_PCR_MUX(1);			//Configure PTC3
	PORTC->PCR[0] |= PORT_PCR_MUX(1);			//Configure PTC0

	//Configure all the pins as output
	GPIOC->PDDR |= (LCD_DB7 | LCD_DB6 | LCD_DB5 |
				LCD_DB4 | LCD_E | LCD_RS | LCD_RW);
}
