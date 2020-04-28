/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    project6_p1.c
 * @brief   Application entry point.
 */
/* Standard includes. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"
#include "task.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_dma.h"
#include "fsl_dmamux.h"


/* My Own */
#include "sin.h"
#include "dac_adc.h"
#include "led.h"
#include "logger.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* The software timer period. */
#define SW_TIMER_PERIOD_MS (100 / portTICK_PERIOD_MS)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* The callback function. */
void SwTimerCallback(TimerHandle_t xTimer); // highest priority 5
void DAC_task(void *threadp); // priority 4
void ADC_task(void *threadp); // priority 3
void DMA_task(void *threadp); // priority 2
void DSP_task(void *threadp); // priority 1

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
SemaphoreHandle_t xBinary_DAC;
SemaphoreHandle_t xBinary_ADC;
SemaphoreHandle_t xBinary_DMA;
SemaphoreHandle_t xBinary_DSP;
SemaphoreHandle_t xBinary_LED;
uint32_t Hundredmsec = 0;
uint32_t target_Hundredmsec;
bool timer_flag;
uint8_t round_count = 0;
/*******************************************************************************
 * Code
 ******************************************************************************/
/*
 * @brief   Application entry point.
 */
/*!
 * @brief Main function
 */
int main(void)
{
    TimerHandle_t SwTimerHandle = NULL;

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    SystemCoreClockUpdate();

    init_table();
    init_table_uint16();
    DAC_ADC_DMA_Init();
    init_LED();

    /* Create the Binary */
	xBinary_DAC = xSemaphoreCreateBinary();
	if(xBinary_DAC == NULL)
	{
		PRINTF("Cannot create xBinary_DAC");
	}

	xBinary_ADC = xSemaphoreCreateBinary();
	if(xBinary_ADC == NULL)
	{
		PRINTF("Cannot create xBinary_ADC");
	}

	xBinary_DMA = xSemaphoreCreateBinary();
	if(xBinary_DMA == NULL)
	{
		PRINTF("Cannot create xBinary_DMA");
	}

	xBinary_DSP = xSemaphoreCreateBinary();
	if(xBinary_DSP == NULL)
	{
		PRINTF("Cannot create xBinary_DSP");
	}

	xBinary_LED = xSemaphoreCreateBinary();
	if(xBinary_LED == NULL)
	{
		PRINTF("Cannot create xBinary_LED");
	}


    /* Create the task, storing the handle. */
    BaseType_t xReturned[4];
    TaskHandle_t xHandle[4] = {NULL};
    xReturned[0] = xTaskCreate(DAC_task, "DAC_task",200,NULL,configMAX_PRIORITIES-1, &xHandle[0]);
    if (xReturned[0] != pdPASS)
    {
    	PRINTF("Cannot create DAC_task");
    }
    xReturned[1] = xTaskCreate(ADC_task, "ADC_task",200,NULL,configMAX_PRIORITIES-2, &xHandle[1]);
    if (xReturned[1] != pdPASS)
    {
    	PRINTF("Cannot create ADC_task");
    }
    xReturned[2] = xTaskCreate(DMA_task, "DMA_task",200,NULL,configMAX_PRIORITIES-3, &xHandle[2]);
    if (xReturned[1] != pdPASS)
    {
    	PRINTF("Cannot create DMA_task");
    }

    xReturned[3] = xTaskCreate(DSP_task, "DSP_task",200,NULL,configMAX_PRIORITIES-4, &xHandle[3]);
    if (xReturned[1] != pdPASS)
    {
    	PRINTF("Cannot create DSP_task");
    }

    /* Create the software timer. */
    SwTimerHandle = xTimerCreate("SwTimer",          /* Text name. */
                                 SW_TIMER_PERIOD_MS, /* Timer period. */
                                 pdTRUE,             /* Enable auto reload. */
                                 0,                  /* ID is not used. */
                                 SwTimerCallback);   /* The callback function. */

    /* Routine explanation */
    /*******************************************************************************
     * 1. Timer task runs every 0.1 sec and release timer Binary
     * 2. DAC task runs when timer Binary release. When done, release DAC Binary .
     * 3. ADC task runs when DAC Binary release, store result in a buffer
     *
     * After 50 rounds of step 1 to step 3, all tasks are ended. And a DSP summary
     * will be printed out
     ******************************************************************************/

    /* Start timer. */
    xTimerStart(SwTimerHandle, 0);
    /* Start scheduling. */
    vTaskStartScheduler();


    /* Infinite While */
    while(1);// should never be here
}

/*!
 * @brief Software timer callback.xBinary_timer
 */
void SwTimerCallback(TimerHandle_t xTimer)
{
	xSemaphoreGive(xBinary_DAC);
	Hundredmsec++;
	if (timer_flag ==true)
	{
		if(Hundredmsec == target_Hundredmsec)
		timer_flag = false;
		turn_LED_blue(off);
		xSemaphoreGive(xBinary_LED);
	}
}

uint32_t timerGetRunTimeHundredmsec(void)
{

	return Hundredmsec;
}

/*!
 * @brief DAC task
 */
void DAC_task(void *threadp)
{
	static int i = 0;
	while(1)
	{
		xSemaphoreTake(xBinary_DAC,portMAX_DELAY);
		if(xSemaphoreTake(xBinary_LED,1)==pdTRUE)
		{
			turn_LED_green(on);
			DAC_Write(i);
			turn_LED_green(off);
			xSemaphoreGive(xBinary_LED);
		}
		else
		{
			DAC_Write(i);
		}

		xSemaphoreGive(xBinary_ADC);
		if(i==50) i = 0;
		else i++;

		if(round_count == 5)vTaskSuspend(NULL);
	}
}

/*!
 * @brief ADC task
 */
void ADC_task(void *threadp)
{
	static int i = 0;
	while(1)
	{
		xSemaphoreTake(xBinary_ADC,portMAX_DELAY);
		ADC_Read(i);

		if(i==64)
		{
			xSemaphoreGive(xBinary_DMA);

			i = 0;
		}
		else i++;

		if(round_count == 5)vTaskSuspend(NULL);
	}
}

/*!
 * @brief ADC task
 */
void DMA_task(void *threadp)
{
	while(1)
	{
		xSemaphoreTake(xBinary_DMA,portMAX_DELAY);
		if(xSemaphoreTake(xBinary_LED,1)==pdTRUE)
		{
			turn_LED_blue(on);
		}
		DMA_Transfer();
		xSemaphoreGive(xBinary_DSP);
		round_count++;
		if(round_count == 5)vTaskSuspend(NULL);

	}
}

void DSP_task(void *threadp)
{
	while(1)
	{
		xSemaphoreTake(xBinary_DSP,portMAX_DELAY);
		DSP_Summary(round_count);
		if(round_count == 5) while(1);
	}
}
