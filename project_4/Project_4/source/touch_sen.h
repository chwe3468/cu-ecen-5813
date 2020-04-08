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

/********************** Define ***********************/
// please only define one of it
//#define L_M_R_POSITION_MODE
#define L_R_POSITION_MODE

/********************** Typedef ***********************/

#ifdef L_M_R_POSITION_MODE
/* enum for slider position */
typedef enum _tsi_position
{
	left = 0U,
	middle = 1U,
	right = 2U
}tsi_position_t;

#endif

#ifdef L_R_POSITION_MODE
/* enum for slider position */
typedef enum _tsi_position
{
	left = 0U,
	right = 1U,
	unknown = 2U
}tsi_position_t;
#endif

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
