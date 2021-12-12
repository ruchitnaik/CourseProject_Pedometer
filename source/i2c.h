/*
 * i2c.c
 *
 *  Created on: Nov 29, 2021
 *      Author: Ruchit Naik
 *       Brief: This file handles the I2C bare-metal code to handle I2C for KL25Z.
 *   Reference: https://www.nxp.com/docs/en/data-sheet/KL25P80M48SF0.pdf
 *   			https://www.nxp.com/downloads/en/schematics/FRDM-KL25Z_SCH_REV_E.pdf
 *   			https://documents.pub/document/kl25-sub-family-reference-manual-nxp-semiconductors-2018-12-20-kl25-sub-family.html
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "MKL25Z4.h"

/**
 * @function I2C_init
 * @brief  	 Initialize the I2C0 module for KL25Z
 * @param    none
 * @return   none
 */
void I2C0_init(void);

/**
 * @function I2C0_busy
 * @brief  	 Initialize the I2C0 module for KL25Z
 * @param    none
 * @return   none
 */
void I2C0_busy(void);

/**
 * @function I2C0_wait
 * @brief  	 Wait for the I2C line to be cleared
 * @param    none
 * @return   none
 */
void I2C0_wait(void);

/**
 * @function I2C0_start
 * @brief  	 Start I2C transfer
 * @param    none
 * @return   none
 */
void I2C0_start(void);

/**
 * @function I2C0_read_setup
 * @brief  	 Set the registers to read the specific register address
 * 			 from the specific device address.
 * @param    dev		Device address from where the data is to be read
 * 			 address	Address of the register from where the data
 * 			 			is to be read
 * @return   none
 */
void I2C0_read_setup(uint8_t dev, uint8_t address);

/**
 * @function I2C0_repeated_read
 * @brief  	 configure the I2C0 for repeated read of registers
 * @param    flag	flag which indicates repeated read is required or not
 * @return   data which is read from the mentioned registered
 */
uint8_t I2C0_repeated_read(uint8_t flag);

/**
 * @function I2C0_read_byte
 * @brief  	 configure the I2C0 to read a single byte
 * @param    dev		Device address from where the data is to be read
 * 			 address	Address of the register from where the data
 * 			 			is to be read
 * @return   data that is read from the register
 */
uint8_t I2C0_read_byte(uint8_t dev, uint8_t address);

/**
 * @function I2C0_write_byte
 * @brief  	 configure the I2C0 to write a single byte
 * @param    dev		Device address from where the data is to be read
 * 			 address	Address of the register from where the data
 * 			 			is to be read
 * 			 data		Data which is to be written on the mentioned register
 * @return   none
 */
void I2C0_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif /* I2C_H_ */
