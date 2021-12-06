/*
 * lcd.h
 *
 *  Created on: Dec 6, 2021
 *      Author: rtrru
 */

#ifndef LCD_H_
#define LCD_H_

#include "MKL25Z4.h"

// LCD Pins naming
#define LCD_DB7  ((uint32_t)1 << 7)  // PTC7
#define LCD_DB6  ((uint32_t)1 << 0)  // PTC0
#define LCD_DB5  ((uint32_t)1 << 3)  // PTC3
#define LCD_DB4  ((uint32_t)1 << 4)  // PTC4

#define LCD_E    ((uint32_t)1 << 5)  // PTC5
#define LCD_RW   ((uint32_t)1 << 6)  // PTC6
#define LCD_RS   ((uint32_t)1 << 10) // PTC10

#endif /* LCD_H_ */
