/*
 * lcd.h
 *
 *  Created on: Dec 6, 2021
 *      Author: Ruchit Naik
 */

#ifndef LCD_H_
#define LCD_H_

#include "MKL25Z4.h"
#include "timer.h"

/************************************************
 * LCD to GPIO pin configuration interface
 ************************************************/
#define LCD_DB7  ((uint32_t)1 << 7)  // PTC7
#define LCD_DB6  ((uint32_t)1 << 0)  // PTC0
#define LCD_DB5  ((uint32_t)1 << 3)  // PTC3
#define LCD_DB4  ((uint32_t)1 << 4)  // PTC4

#define LCD_E    ((uint32_t)1 << 5)  // PTC5
#define LCD_RW   ((uint32_t)1 << 6)  // PTC6
#define LCD_RS   ((uint32_t)1 << 10) // PTC10

//lcd_line denotes the line number on the LCD. If the new API needs
//to be called then, SAME_LINE is used which preserves the cursor
//on the last cursor location.
typedef enum{
	LCD_LINE1,
	LCD_LINE2,
	SAME_LINE
}lcd_line;

/**
 * @function lcd_init
 * @brief  	 Initialize the GPIO to interface the 16x2 LCD over it.
 * 			 GPIO port C is used for configuration
 * @param    none
 * @return   none
 */
void lcd_init(void);

/**
 * @function write_nibble
 * @brief  	 write 4 bits on the LCD DDRAM. The function handles
 * 			 either upper or lower nibble to be written on DDRM.
 * @param    nibble		The value of the nibble which is to be
 * 						writtern on the register.
 * @return   none
 */
void write_nibble(uint8_t nibble);

/**
 * @function lcd_cmd
 * @brief  	 sends the command to the device. The command is
 * 			 written directly on the memory.
 * @param    cmd	command which is to be sent to the device.
 * @return   none
 */
void lcd_cmd(uint8_t cmd);

/**
 * @function start_lcd
 * @brief  	 Function to send the commands to the LCD to get
 * 			 the LCD in the desired original state. It mainly
 * 			 sets the position of the cursor and set the mode
 * 			 of operation of the LCD. It also clears the display
 * 			 to start the program routine.
 * @param    none
 * @return   none
 */
void start_lcd(void);

/**
 * @function clear_lcd
 * @brief  	 Clears the LCD to display new screen clearly.
 * @param    none
 * @return   none
 */
void clear_lcd(void);

/**
 * @function lcd_string_write
 * @brief  	 write the string on the display. It prints the
 * 			 entire string on the LCD.
 * @param    str	pointer to the char pointer which holds
 * 					the string which needs to be printed
 * @return   cnt	Count of data which is written on the LCD.
 */
uint8_t lcd_string_write(char **str);

/**
 * @function lcd_data_write
 * @brief  	 handles the string to be written on the LCD.
 * 			 The function handles the line where it is to
 * 			 be printed. It sets the courser to the desired
 * 			 location and the character pointer to the string
 * 			 which is to be printed
 * @param    data	character pointer to the string which is to
 * 					be printed
 * 			 line	The line number where the data line is to be
 * 			 		printed. It accepts datatype 'lcd_line'. If
 * 			 		input is SAME_LINE, it retains the current
 * 			 		cursor location.
 * @return   none
 */
void lcd_data_write(char *data, lcd_line line);

/**
 * @function lcd_data_write_int
 * @brief  	 function which handles to write integer on
 * 			 the LCD. It converts the input integer to
 * 			 ASCII to be printed on the LCD. It can handle
 * 			 10 digit long number
 * @param    num	Integer which is to be printed on screen
 * 			 line	The enum which specifies the line number
 * 			 		on which new message is to be printed.
 * @return   none
 */
void lcd_data_write_int(uint32_t num, lcd_line line);

#endif /* LCD_H_ */
