/*
 * log.c
 *
 *  Created on: Dec 18, 2018
 *      Author: Chutao Wei
 *
 */
/********************** Include ***********************/

#include <stdint.h>
#include "logger.h"


/********************** Global ***********************/

log_status_t log_status = disable;


/********************** Functions ***********************/
void Log_enable(void)
{
	log_status = enable;
}

void Log_disable(void)
{
	log_status = disable;
}

log_status_t Log_status(void)
{
	return log_status;
}

void Log_data(uint32_t data)
{
	if(log_status == enable)
	{
		printf("Addr: 0x%08x, Data: 0x%08x",&data,data);
	}
}

void Log_string(const char * str)
{
	if(log_status == enable)
	{
		printf("%s\n", str);
	}
}

void Log_integer(int integer)
{
	if(log_status == enable)
	{
		printf("%d\n", integer);
	}
}
