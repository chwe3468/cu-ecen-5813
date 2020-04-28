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
#include "project6_p2.h"
/********************** Global ***********************/

log_status_t log_status = disable;


/********************** Functions ***********************/

/**
 * @return a timestamp value for the logger, typically based on a free running timer.
 * This will be printed at the beginning of each log message.
 */

uint32_t loggerGetTimestamp(void)
{
	return (uint32_t)(timerGetRunTimeHundredmsec());
}
#ifdef HMS_FORMAT
uint32_t loggerGetTimestampHour()
{
	uint64_t msec = timerGetRunTimeMilliseconds();
	return (uint32_t)(msec/360000);
}
uint32_t loggerGetTimestampMinute()
{
	uint64_t msec = timerGetRunTimeMilliseconds();
	return (uint32_t)(msec/6000);
}
uint32_t loggerGetTimestampSecond()
{
	uint64_t msec = timerGetRunTimeMilliseconds();
	return (uint32_t)(msec/1000);
}
uint32_t loggerGetTimestampTenthSec()
{
	uint64_t msec = timerGetRunTimeMilliseconds();
	return (uint32_t)(msec/100);
}
#endif
