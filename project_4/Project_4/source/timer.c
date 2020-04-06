/*
 * timer.c
 *
 *  Created on: Feb 11, 2020
 *      Author: chutao
 */

/*************** Include *****************/

#include <logger.h>
#include <stdint.h>
#include <MKL25Z4.h>


/*************** Define *****************/

#define CPU_FREQ_MHZ	(48)
#define NUM_ASSE_FOR	(7)
#define DELAY_MS_TO_LOOP_COUNT(msec)\
	((uint32_t)((msec*(CPU_FREQ_MHZ*1000))/(NUM_ASSE_FOR)))


/*************** Global Variables *****************/
const uint32_t delay_look_up_table[] = {
		DELAY_MS_TO_LOOP_COUNT(500),
		DELAY_MS_TO_LOOP_COUNT(1000),
		DELAY_MS_TO_LOOP_COUNT(2000),
		DELAY_MS_TO_LOOP_COUNT(3000)};


/*************** Function *****************/

void delay_ms(uint32_t msec)
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

void Init_SysTick(void) {
	SysTick->LOAD = (48000000L / 6);
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk |\
 SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler() {
	static int n = 0;
	if (n<5){

	}
	Control_RGB_LEDs(n & 1, n & 1, n & 1);
	n++;
}

