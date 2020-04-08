/*
 * timer.c
 *
 *  Created on: Feb 11, 2020
 *      Author: chutao
 */

/*************** Include *****************/

#include <logger.h>
#include <stdint.h>
#include <stdbool.h>
#include "state.h"

/*************** Define *****************/

#define INCLUDE_LOG_DEBUG 1
#define CPU_FREQ_MHZ	(48)
#define NUM_ASSE_FOR	(7)
#define DELAY_MS_TO_LOOP_COUNT(msec)\
	((uint32_t)((msec*(CPU_FREQ_MHZ*1000))/(NUM_ASSE_FOR)))
//#define BLOCKWAITING

/*************** Global Variables *****************/

const uint32_t delay_look_up_table[] = {
		DELAY_MS_TO_LOOP_COUNT(500),
		DELAY_MS_TO_LOOP_COUNT(1000),
		DELAY_MS_TO_LOOP_COUNT(2000),
		DELAY_MS_TO_LOOP_COUNT(3000)};

uint64_t msec_count = 0;
uint64_t target_msec_count = 0;
bool delay_flag = 0;
/* Time out count for kWaitPollSlider state */
uint8_t timeout_count = 0;
/*************** Interrupt Hanlder ****************/

void SysTick_Handler(void)
{
	msec_count ++;
	if (delay_flag == true)
	{
		if (msec_count == target_msec_count)
		{
			delay_flag = false;
			timeout_count++;
			if (timeout_count == 6)
			{
				timeout_count = 0;
				SetEvent(Timeout_6);
			}
			else
			{
				SetEvent(Timeout_1_5);
			}
		}
	}
}

/*************** Function *****************/

void Init_SysTick(void) {
	SysTick->LOAD = (48000L-1L);// count 1 msec
	NVIC_SetPriority(SysTick_IRQn, 3); // enable NVIC
	SysTick->VAL = (480000L-1L); // reset count value
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

}

#ifdef BLOCK_WAITING
// Block waiting function abandoned for now
void mdelay(uint32_t msec)
{
	LOG_DEBUG("Blocking wait for %d msec", msec);
	uint32_t i = 0;
	uint32_t delay_count = 0;
	if (msec == 500)
	{
		delay_count = delay_look_up_table[0];
	}
	else if (msec == 1000)
	{
		delay_count = delay_look_up_table[1];
	}
	else if (msec == 2000)
	{
		delay_count = delay_look_up_table[2];
	}
	else if (msec == 3000)
	{
		delay_count = delay_look_up_table[3];
	}
	else
	{
		LOG_ERROR("Unexpected msec value, has to be 500, 1000, 2000, 3000");
	}
	for(i=0; i<delay_count; i++);
}
#else
// Interrupt waiting function4
void mdelay(uint32_t msec)
{
	LOG_DEBUG("Interrupt wait for %d msec", msec);
	// read current count
	target_msec_count = msec_count + msec;
	delay_flag = true;
}
#endif
