/*
 * timer.h
 *
 *  Created on: Feb 11, 2020
 *      Author: chutao
 */

#ifndef TIMER_H_
#define TIMER_H_


/*************** Include *****************/

#include <stdint.h>
#include "MKL25Z4.h"


/*************** Define *****************/

#define CPU_FREQ_MHZ	(48)
#define NUM_ASSE_FOR	(7)


/*************** Prototype *****************/

/*************************************************
 * @brief
 *   Initialize Systick timer for 1 msec period
 *   counting. This period timer is also used for
 *   mdelay to track counter value
 ************************************************/
void Init_SysTick(void);

/*************************************************
 * @brief
 *   Block delay for msec amount of microsecond
 ************************************************/
void mdelay(uint32_t msec);


#endif /* TIMER_H_ */
