/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Course_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "mma8451.h"
#include "timer.h"
#include "utility.h"
#include "lcd.h"
#include "button.h"
#include "tsi.h"
/* TODO: insert other definitions and declarations here. */
int16_t xval[100] = {0};
int16_t yval[100] = {0};
int16_t zval[100] = {0};
int xavg, yavg, zavg;
int16_t total_vect[100] = {0};
int16_t total_avg[100] = {0};
uint16_t step_count = 0;

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
#ifdef DEBUG
    PRINTF("WELCOME TO PEDOMETER MANUAL TESTING\r\n");
    PRINTF("Initialization in progress...\r\n\n");
#endif

    init_systick();
    I2C0_init();
    button_Init();
    TSI_Init();
    if(!init_mma()){				//Initialize accelerometer hardware
    	while(1);
    }
    lcd_init();

#ifdef DEBUG
    PRINTF("Initialization completed\r\n\n");
    PRINTF("****************************************************************\r\n");
    PRINTF("calibrating....\r\n\n");
#endif
    calibrate(xval, yval, zval, &xavg, &yavg, &zavg);
    delay(1000);

#ifdef DEBUG
    PRINTF("Calibration completed\r\n\n");
    PRINTF("Calibrated avg values X: %d, Y: %d, Z: %d\r\n", xavg, yavg, zavg);
    PRINTF("****************************************************************\r\n");
#endif

    start_lcd();
    lcd_data_write("PEDOMETER", LCD_LINE1);
    lcd_data_write("Version 1.0", LCD_LINE2);
    delay(2000);
    clear_lcd();								//Clear display
	lcd_data_write("Counting Steps...", LCD_LINE2);
	lcd_data_write("PEDOMETER", LCD_LINE1);
	delay(2000);
	clear_lcd();
    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        if(i<100){
        	step_count = detect_step(step_count, i);
#ifdef DEBUG
        	PRINTF("STEPS: %d\r\n", step_count);
#endif
        	lcd_data_write("STEPS:", LCD_LINE1);
        	lcd_data_write_int(step_count, SAME_LINE);
        	lcd_data_write("Counting Steps...", LCD_LINE2);
        }
        else{
        	i=0;
        }
        if((TSI_Detect()) || (get_flagSwitch())){
        	step_count = 0;
#ifdef DEBUG
        	if(get_flagSwitch()){
        		PRINTF("Pedometer Reseted by Push Button\r\n");
        	}
        	else{
        		PRINTF("Pedometer Reseted by TSI Touch\r\n");
        	}
#endif
        	clear_lcd();
            lcd_data_write("STEPS:", LCD_LINE1);
            lcd_data_write_int(step_count, SAME_LINE);
            lcd_data_write("RESET", LCD_LINE2);
        }
    }
    return 0 ;
}
