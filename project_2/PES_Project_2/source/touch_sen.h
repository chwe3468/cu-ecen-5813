/*
 * touch_sen.h
 *
 *  Created on: Feb 11, 2020
 *  	Author: Freescale
 *  	link: https://www.digikey.com/eewiki/display/microcontroller/Using+the+Capacitive+Touch+Sensor+on+the+FRDM-KL46Z
 *      Editor: chutao
 */

#ifndef TOUCH_SEN_H_
#define TOUCH_SEN_H_

/*************** Include *****************/

#include "MKL25Z4.h"


/********************** Typedef ***********************/

/* enum for slider position */
typedef enum _tsi_position
{
	left = 0U,
	middle = 1U,
	right = 2U
}tsi_position_t;


/*************** Define *****************/

#define SCAN_OFFSET 544  // Offset for scan range
#define SCAN_DATA TSI0->DATA & 0xFFFF // Accessing the bits held in TSI0_DATA_TSICNT


/*************** Prototype *****************/

// Touch Sensor function prototypes
void Touch_Init(void);
int Touch_Scan_LH(void);
int Touch_Scan_HL(void);
tsi_position_t Touch_Scan_Position(void);

#endif /* TOUCH_SEN_H_ */
