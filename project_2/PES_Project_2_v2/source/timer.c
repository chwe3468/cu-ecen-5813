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
	LOG_DEBUG("Blocking wait for %d msec",delay*1000);
	time(&start_t);

	while (diff_t<(double)delay/1000.0){
	time(&end_t);
	diff_t = difftime(end_t, start_t);
	}
}

void pc_run(void)
{
	// Declare pattern
	double pattern[8] = {.5, .5, 1, .5, 2, .5, 3, .5};

	uint32_t i = 0;
	int32_t c = 0;
	int32_t color_index = 0;
	while(1){
			for(i=0; i<8; i++)
			{
				if(PC){
					if(!(i&0x1)){ //if even turn on else turn off according to color_index
						if (color_index==0){
							printf("LED RED ON\n");
							LOG_DEBUG("Turn LED RED ON %s");
						}
						else if(color_index==1){
							printf("LED GREEN ON\n");
							LOG_DEBUG("Turn LED GREEN ON %s");
						}
						else{
							printf("LED BLUE ON\n");
							LOG_DEBUG("Turn LED BLUE ON %s");
						}
					}
					else{
						if (color_index==0){
							printf("LED RED OFF\n");
							LOG_DEBUG("Turn LED RED OFF %s");
						}
						else if(color_index==1){
							printf("LED GREEN OFF\n");
							LOG_DEBUG("Turn LED GREEN OFF %s");
						}
						else{
							printf("LED BLUE OFF\n");
							LOG_DEBUG("Turn LED BLUE OFF %s");
						}
					}
				}
				// Can only change color if loop count is even
				if (!(i&0x1))
				{
					if(PC){
						if (c>=6){
							if (color_index>=2){
								color_index=-1;
							}
							color_index++;
							c=-1;
						}
					}
				}
				c++;
				time_it(pattern[i]);
			}
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
