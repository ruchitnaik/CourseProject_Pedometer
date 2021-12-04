/*
 * i2c.h
 *
 *  Created on: Nov 29, 2021
 *      Author: Ruchit Naik
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "MKL25Z4.h"

void I2C_init(void);
void i2c_busy(void);
void i2c_wait(void);
void i2c_start(void);
void i2c_read_setup(uint8_t dev, uint8_t address);
uint8_t i2c_repeated_read(uint8_t flag);
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif /* I2C_H_ */
