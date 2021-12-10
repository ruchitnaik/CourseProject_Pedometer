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

// LCD Pins naming
#define LCD_DB7  ((uint32_t)1 << 7)  // PTC7
#define LCD_DB6  ((uint32_t)1 << 0)  // PTC0
#define LCD_DB5  ((uint32_t)1 << 3)  // PTC3
#define LCD_DB4  ((uint32_t)1 << 4)  // PTC4

#define LCD_E    ((uint32_t)1 << 5)  // PTC5
#define LCD_RW   ((uint32_t)1 << 6)  // PTC6
#define LCD_RS   ((uint32_t)1 << 10) // PTC10

typedef enum{
	LCD_LINE1,
	LCD_LINE2,
	SAME_LINE
}lcd_line;

void lcd_init(void);
void write_nibble(uint8_t nibble);
void lcd_cmd(uint8_t cmd);
void start_lcd(void);
uint8_t lcd_string_write(char **str);
void lcd_data_write(char *data, lcd_line line);
void lcd_data_write_int(uint32_t num, lcd_line line);

#endif /* LCD_H_ */
