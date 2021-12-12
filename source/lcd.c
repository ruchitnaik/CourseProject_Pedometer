/*
 * lcd.c
 *		 Brief: The file handles the driver for 16x2 LCD in 4-bit mode.
 *		 		The LCD is configured to be interface on Port C.
 *		 		If LCD does not display anything on the screen, it could
 *		 		be because of:
 *		 		- insufficient delay added between HIGH to LOW transmission on
 *		 		Enable pin.
 *		 		- Invalid LCD command
 *		 		- Invalid LCD Data
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


void write_nibble(uint8_t nibble){
	uint32_t gpio_temp;

	//Get GPIOC Data Register
	gpio_temp = GPIOC->PDOR;

	//Update the LCD data line DB7
	if(nibble & 0x80){
		gpio_temp |= LCD_DB7;
	}
	else{
		gpio_temp &= ~LCD_DB7;
	}

	//Update the LCD data line DB6
	if(nibble & 0x40){
		gpio_temp |= LCD_DB6;
	}
	else{
		gpio_temp &= ~LCD_DB6;
	}

	//Update the LCD data line DB5
	if(nibble & 0x20){
		gpio_temp |= LCD_DB5;
	}
	else{
		gpio_temp &= ~LCD_DB5;
	}

	//Update the LCD data line DB4
	if(nibble & 0x10){
		gpio_temp |= LCD_DB4;
	}
	else{
		gpio_temp &= ~LCD_DB4;
	}

	GPIOC->PDOR = gpio_temp;					//Write - Update data on GPIO Port C
}


void lcd_cmd(uint8_t cmd){
	GPIOC->PDOR &= ~LCD_RS;						//Select command register (RS=Low)
	GPIOC->PDOR &= ~LCD_RW;						//Select write operation (RW=Low)

	write_nibble(cmd & 0xF0);					//Write upper nibble

	//Generate High to Low pulse on EN pin
	GPIOC->PDOR |= LCD_E;						//EN = High
	delay(1);
	GPIOC->PDOR &= ~LCD_E;						//EN = Low
	delay(1);

	write_nibble((cmd<<4) & 0xF0);				//Write lower nibble

	//Generate High to Low pulse on EN pin
	GPIOC->PDOR |= LCD_E;						//EN = High
	delay(1);
	GPIOC->PDOR &= ~LCD_E;						//EN = Low
	delay(1);
}


void start_lcd(void){
	lcd_cmd(0x02);								//Cursor on original position
	delay(10);
	lcd_cmd(0x28);								//Enable 4-bit, 2 line, 5x7 dots mode for characters
	delay(10);
	lcd_cmd(0x0C);								//Display ON, Cursor OFF
	delay(10);
	lcd_cmd(0x01);								//Clear display
	delay(10);
}

void clear_lcd(void){
	lcd_cmd(0x01);								//Clear display
	delay(10);
}

uint8_t lcd_string_write(char **str){
	uint8_t cnt = 0;							//Counting String length

	//Write the complete message
	while(**str && (cnt<16)){
		GPIOC->PDOR |= LCD_RS;					//Select data register for LCD
		GPIOC->PDOR &= ~LCD_RW;					//Select write mode

		write_nibble(**str & 0xF0);				//Writing upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		write_nibble((**str << 4) & 0xF0);				//Writing upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		(*str)++;								//Moving the pointer to next character
		cnt++;
		delay(10);
	}
	return cnt;
}

void lcd_data_write(char *data, lcd_line line){
	uint8_t char_written;						//Actual no. of chars written on LCD
	char *temp = " ";							//Space to be filled for unused blocks on line

	//Set cursor to the specific line where it is to be writtern
	switch(line){
	case LCD_LINE1:
		lcd_cmd(0x80);							//Move the cursor to the beginning of first line
		break;

	case LCD_LINE2:
		lcd_cmd(0xC0);							//Move the cursor to the beginning of second line
		break;

	case SAME_LINE:								//Writes on the same line where the cursor currently is
		break;
	}

	//Write data string to LCD (it returns how many characters are written)
	char_written = lcd_string_write(&data);
	while(char_written < 16){
		lcd_string_write(&temp);
		char_written++;
	}
}


void lcd_data_write_int(uint32_t num, lcd_line line){
	uint8_t byte[10] = {0};							//Handle upto 10 digits
	uint8_t idx = 0;							//Index to preserve the state of byte array

	//Set cursor to the specific line where it is to be writtern
	switch(line){
	case LCD_LINE1:
		lcd_cmd(0x80);							//Move the cursor to the beginning of first line
		break;

	case LCD_LINE2:
		lcd_cmd(0xC0);							//Move the cursor to the beginning of second line
		break;

	case SAME_LINE:								//Writes on the same line where the cursor currently is
		break;
	}

	//Recovering each digit from the input
	while(num != 0){
		byte[idx] = num % 10;
		num = num / 10;
		idx++;
	}

	//Convert the decimal into ASCII and print on the LCD
	for(int i=(idx - 1); i>=0; i--){
		GPIOC->PDOR |= LCD_RS;					//Select data register
		GPIOC->PDOR &= ~LCD_RW;					//Select write mode

		write_nibble(('0'+byte[i]) & 0xF0);		//Write upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		write_nibble((('0'+byte[i]) << 4) & 0xF0);	//Write lower nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		delay(10);
	}
	if(idx == 0){
		GPIOC->PDOR |= LCD_RS;					//Select data register
		GPIOC->PDOR &= ~LCD_RW;					//Select write mode

		write_nibble(('0'+byte[idx]) & 0xF0);		//Write upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		write_nibble((('0'+byte[idx]) << 4) & 0xF0);	//Write lower nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(1);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(1);

		delay(10);
	}
}
