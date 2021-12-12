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

#include "i2c.h"

int lock_detect = 0;
int i2c_lock = 0;

/**
 * @function I2C0_init
 * @brief  	 Initialize the I2C0 module for KL25Z
 * @param    none
 * @return   none
 */
void I2C0_init(void){
	//Enabling clock to I2C0 module and GPIO Port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//Set pins to I2C functionality
	PORTE->PCR[24] |= PORT_PCR_MUX(5);	//Setting I2C0_SCL pin configuration
	PORTE->PCR[25] |= PORT_PCR_MUX(5);	//Setting I2C0_SDA pin configuration

	I2C0->F = (I2C_F_MULT(0) | I2C_F_ICR(0X10));

	//Enable I2C and set it to master mode
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	//Select high drive mode
	I2C0->C2 |= I2C_C2_HDRS_MASK;
}

/**
 * @function I2C0_busy
 * @brief  	 Initialize the I2C0 module for KL25Z
 * @param    none
 * @return   none
 */
void I2C0_busy(void){
	lock_detect = 0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_TX_MASK;		//Set to transmit mode
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	//Clear I2C line
	I2C0->C1 |= I2C_C1_MST_MASK;	//Set Master mode
	I2C0->C1 |= I2C_C1_TX_MASK;		//Set Tx mode
	I2C0->D = 0xFF;
	while((I2C0->S & I2C_S_IICIF_MASK) == 0U){
	}								//wait interrupt
	I2C0->S |= I2C_S_IICIF_MASK;	//clear interrupt bit

	I2C0->S |= I2C_S_ARBL_MASK;		//Clear arbitration error flag

	I2C0->C1 &= ~I2C_C1_IICEN_MASK;	//Send start
//	I2C0->C1 |= I2C_C1_TX_MASK;		//set transmitter mode
	I2C0->C1 |= I2C_C1_MST_MASK;	//Start signal generated

	I2C0->C1 |= I2C_C1_IICEN_MASK;

	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK;	//Set slave mode
	I2C0->C1 &= ~I2C_C1_TX_MASK;	//Set Rx
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;		//Clear arbitration error and interrupt flag
	lock_detect = 0;
	i2c_lock = 1;
}

/**
 * @function I2C0_wait
 * @brief  	 Wait for the I2C line to be cleared
 * @param    none
 * @return   none
 */
void I2C0_wait(void){
	lock_detect = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK) == 0) & (lock_detect < 200)){
		lock_detect++;
	}
	if(lock_detect >= 200){
		I2C0_busy();
	}
	I2C0->S |= I2C_S_IICIF_MASK;
}

/**
 * @function I2C0_start
 * @brief  	 Start I2C transfer
 * @param    none
 * @return   none
 */
void I2C0_start(void){
	I2C0->C1 |= I2C_C1_TX_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
}

/**
 * @function I2C0_read_setup
 * @brief  	 Set the registers to read the specific register address
 * 			 from the specific device address.
 * @param    dev		Device address from where the data is to be read
 * 			 address	Address of the register from where the data
 * 			 			is to be read
 * @return   none
 */
void I2C0_read_setup(uint8_t dev, uint8_t address){
	I2C0->D = dev;					//Send device address
	I2C0_wait();

	I2C0->D = address;				//Send read address
	I2C0_wait();

	I2C0->C1 |= I2C_C1_RSTA_MASK;	//Restart
	I2C0->D = (dev|0x1);			//Send dev address (read)
	I2C0_wait();

	I2C0->C1 &= ~I2C_C1_TX_MASK;	//Set to receive mode
}

/**
 * @function I2C0_repeated_read
 * @brief  	 configure the I2C0 for repeated read of registers
 * @param    flag	flag which indicates repeated read is required or not
 * @return   data which is read from the mentioned registered
 */
uint8_t I2C0_repeated_read(uint8_t flag){
	uint8_t data;
	lock_detect = 0;

	if(flag){
		I2C0->C1 |= I2C_C1_TXAK_MASK;
	}
	else{
		I2C0->C1 &= ~I2C_C1_TXAK_MASK;
	}

	data = I2C0->D;					//Backup read data locally
	I2C0_wait();

	if(flag){
		I2C0->C1 &= ~I2C_C1_MST_MASK;
	}
	data = I2C0->D;					//Read data

	return data;
}

/**
 * @function I2C0_read_byte
 * @brief  	 configure the I2C0 to read a single byte
 * @param    dev		Device address from where the data is to be read
 * 			 address	Address of the register from where the data
 * 			 			is to be read
 * @return   data that is read from the register
 */
uint8_t I2C0_read_byte(uint8_t dev, uint8_t address){
	uint8_t data;

	I2C0->C1 |= I2C_C1_TX_MASK;		//Set to transmit mode
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;	//Send start
	I2C0->D = dev;					//Send device address
	I2C0_wait();

	I2C0->D = address;				//Send read address
	I2C0_wait();

	I2C0->C1 |= I2C_C1_RSTA_MASK;	//Repeated start
	I2C0->D = (dev|0x1);			//Send development address - read
	I2C0_wait();

	I2C0->C1 &= ~I2C_C1_TX_MASK;	//Set to receive mode
	I2C0->C1 |= I2C_C1_TXAK_MASK;	//Set NACK after read

	data = I2C0->D;					//Read backup
	I2C0_wait();

	I2C0->C1 &= ~I2C_C1_MST_MASK;	//Send stop
	data = I2C0->D;					//Read data

	return data;
}

/**
 * @function I2C0_write_byte
 * @brief  	 configure the I2C0 to write a single byte
 * @param    dev		Device address from where the data is to be read
 * 			 address	Address of the register from where the data
 * 			 			is to be read
 * 			 data		Data which is to be written on the mentioned register
 * @return   none
 */
void I2C0_write_byte(uint8_t dev, uint8_t address, uint8_t data){
	I2C0->C1 |= I2C_C1_TX_MASK;		//Set to transmit mode
	I2C0->C1 |= I2C_C1_MST_MASK;	//Send start
	I2C0->D = dev;					//Send device address
	I2C0_wait();

	I2C0->D = address;				//Send write address
	I2C0_wait();

	I2C0->D = data;					//Send data
	I2C0_wait();
	I2C0->C1 &= ~I2C_C1_MST_MASK;	//Send stop bit
}
