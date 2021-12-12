/*
 * tsi.c
 *
 *  Created on: Dec 11, 2021
 *      Author: Ruchit Naik
 */

#include "tsi.h"

/**
 * @function TSI_Init
 * @brief  	 Initializes the parameters for the capacitive touch sensor
 * @param    none
 * @return   none
 */
void TSI_Init(void){
	//Enable clock to TSI module
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;

	//Setting the GENCS to initialize TSI module
	TSI0->GENCS = TSI_GENCS_MODE(0u)|					//enable to operate in non-noise mode
				  //Ref Osc charge and discharge value 500nA
				  TSI_GENCS_REFCHRG(0u)|
				  //Osc voltage rails set to default
				  TSI_GENCS_DVOLT(0u)|
				  //Electrode Osc charge and discharge value 500nA
				  TSI_GENCS_EXTCHRG(0u)|
				  //Setting the module to scan electrods for 32 times
				  TSI_GENCS_NSCN(31u)|
				  //Freq clock divided by 1
				  TSI_GENCS_PS(0u)|
				  //Enabling TSI module
				  TSI_GENCS_TSIEN_MASK|
				  //Writing 1 to clear the end of scan flag
				  TSI_GENCS_EOSF_MASK;
}

/**
 * @function TSI_Detect
 * @brief  	 Detect the touch sensor to return if touch is detected or not
 * @param    none
 * @return   bool true 	if touch detected
 * 				  false if touch not detected
 */
bool TSI_Detect(void){
	bool result_tsi = false;
	uint32_t scan = 0;
	TSI0->DATA = TSI_DATA_TSICH(10u);								//Enable CH10 for data scanning from TSI module
	TSI0->DATA |= TSI_DATA_SWTS_MASK;								//Software trigger to start the scan
	while(!((TSI0->GENCS) & TSI_GENCS_EOSF_MASK));					//Waiting for 32 scans

#ifdef ENABLE_DEBOUNCE
	for(int i=0; i<DEBOUNCE_ITERATIONS; i++){
		scan = scan + ((TSI0->DATA & 0xFFFF)/DEBOUNCE_ITERATIONS);	//Masking the scanned reading bits out of the DATA field
//		scan = scan / DEBOUNCE_ITERATIONS;
		Delay_ms((50/DEBOUNCE_ITERATIONS), false);
	}
#else
	scan = TSI0->DATA & TSI_DATA_TSICNT_MASK/*0xFFFF*/;				//Masking the scanned reading bits out of the DATA field
#endif

	TSI0->GENCS |= TSI_GENCS_EOSF_MASK;								//Clearing the end of scan flag

#ifdef DEBUG
	PRINTF("SLIDER VALUE: %d\r\n", (scan - TOUCH_OFFSET));
#endif

	if((scan-TOUCH_OFFSET) > TOUCH_MIN_THRESHOLD){
#ifdef DEBUG
	PRINTF("SLIDER DETECT: True\r\n");
#endif
		result_tsi = true;
	}
	else{
#ifdef DEBUG
	PRINTF("SLIDER DETECT: false\r\n");
#endif
		result_tsi = false;
	}
	return result_tsi;
}
