/*
 * timer.c
 *
 *  Created on: Feb 11, 2020
 *      Author: chutao
 */

/*************** Include *****************/

#include <stdint.h>
#include "log.h"


/*************** Define *****************/
#if PC_RUN
#define CPU_FREQ_MHZ	(48U)
#include <time.h>
#else
#define CPU_FREQ_MHZ	(48U)
#endif

#define NUM_ASSE_FOR	(7U)
#define DELAY_MS_TO_LOOP_COUNT(msec)\
	((uint32_t)((msec*(CPU_FREQ_MHZ*1000U))/(NUM_ASSE_FOR)))



/*************** Global Variables *****************/
const uint32_t delay_look_up_table[] = {
		DELAY_MS_TO_LOOP_COUNT(500),
		DELAY_MS_TO_LOOP_COUNT(1000),
		DELAY_MS_TO_LOOP_COUNT(2000),
		DELAY_MS_TO_LOOP_COUNT(3000)};


/*************** Function *****************/

//edited from https://www.tutorialspoint.com/c_standard_library/c_function_difftime.htm
void time_it(double delay){

	time_t start_t, end_t;
	double diff_t=-5;
	LOG_DEBUG("Blocking wait for %f msec", (delay*1000));
	time(&start_t);

	while (diff_t<(double)delay){
	time(&end_t);
	diff_t = difftime(end_t, start_t);
	}
}

const char * LED_state[] = {"on", "off"};
const char * LED_color[] = {"red", "green", "blue"};

void pc_run(void)
{
	// Declare pattern
	double pattern[8] = {.5, .5, 1, .5, 2, .5, 3, .5};
	uint32_t i = 0;

	while(1)
	{
		printf("LED %s %s\n", LED_color[(i/6)%3], LED_state[i%2]);
		LOG_DEBUG("Turn LED %s %s\n", LED_color[(i/6)%3], LED_state[i%2]);
		time_it(pattern[i%8]);
		i++;
	}
}

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
