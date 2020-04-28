/*
 * dac_adc.c
 *
 *  Created on: Apr 27, 2020
 *      Author: chutao
 */
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "queue.h"
#include "task.h"

#include "dac_adc.h"
#include "fsl_dac.h"
#include "fsl_adc16.h"
#include "fsl_debug_console.h"
#include "fsl_dma.h"
#include "fsl_dmamux.h"
#include "MKL25Z4.h"
#include "sin.h"
#include "project6_p2.h"
#include "math.h"
#include "logger.h"
/*******************************************************************************
 * Defines
 ******************************************************************************/
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL 0U /* PTE20, ADC0_SE0 */
#define NUM_POINTS 50
#define DMA_CHANNEL 0
#define DMA_SOURCE 63
#define BUF_SIZE 64

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
volatile bool g_Adc16ConversionDoneFlag = false;
volatile uint32_t g_Adc16ConversionValue = 0;
adc16_channel_config_t g_adc16ChannelConfigStruct;

dma_handle_t g_DMA_Handle;
volatile bool g_Transfer_Done = false;

uint16_t ADC_buf[BUF_SIZE];
uint16_t DSP_buf[BUF_SIZE];

unsigned int DMA_start_time;
unsigned int DMA_end_time;
/*******************************************************************************
 * Code
 ******************************************************************************/
// code provided by the fsl library
uint16_t average(uint16_t arr[], uint32_t n)
{
    int i;
    int average = arr[0];
    for (i = 0; i < n; i++)
    	average = average + arr[i];
    return (average/n);
}
// source: https://www.geeksforgeeks.org/c-program-find-largest-element-array/
uint16_t max(uint16_t arr[], uint32_t n)
{
    int i;
    int max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

uint16_t min(uint16_t arr[], uint32_t n)
{
    int i;
    int min = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}
// from https://www.programiz.com/c-programming/examples/standard-deviation
uint16_t SD(uint16_t arr[], uint16_t mean,  uint32_t n)
{
    uint32_t variance = 0;
    int i;
    for (i = 0; i < 10; ++i)
    	variance += pow(arr[i] - mean, 2);
    return sqrt(variance / n);
}

// interrupt hanlder
void ADC0_IRQHandler(void)
{
    g_Adc16ConversionDoneFlag = true;
    /* Read conversion result to clear the conversion completed flag. */
    g_Adc16ConversionValue = ADC16_GetChannelConversionValue(ADC0, DEMO_ADC16_CHANNEL_GROUP);
}

/* User callback function for DMA transfer. */
void DMA_Callback(dma_handle_t *handle, void *param)
{
    g_Transfer_Done = true;
}
// init function
void DAC_ADC_DMA_Init(void)
{
	EnableIRQ(ADC0_IRQn);
    adc16_config_t adc16ConfigStruct;
    dac_config_t dacConfigStruct;

    /* Configure the DAC. */
    /*
     * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
     * dacConfigStruct.enableLowPowerMode = false;
     */
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DAC0, &dacConfigStruct);
    DAC_Enable(DAC0, true); /* Enable output. */

    /* Configure the ADC16. */
    /*
     * adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adc16ConfigStruct.enableAsynchronousClock = true;
     * adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
     * adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;
     * adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
     * adc16ConfigStruct.enableHighSpeed = false;
     * adc16ConfigStruct.enableLowPower = false;
     * adc16ConfigStruct.enableContinuousConversion = false;
     */
    ADC16_GetDefaultConfig(&adc16ConfigStruct);
#if defined(BOARD_ADC_USE_ALT_VREF)
    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif
    ADC16_Init(ADC0, &adc16ConfigStruct);

    /* Make sure the software trigger is used. */
    ADC16_EnableHardwareTrigger(ADC0, false);
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(ADC0))
    {
        //PRINTF("\r\nADC16_DoAutoCalibration() Done.");
    }
    else
    {
        //PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

    /* Prepare ADC channel setting */
    g_adc16ChannelConfigStruct.channelNumber = DEMO_ADC16_USER_CHANNEL;
    g_adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = true;

#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    g_adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
    /* Configure DMAMUX */
    DMAMUX_Init(DMAMUX0);
    DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL, DMA_SOURCE);
    DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL);
    /* Configure DMA one shot transfer */
    DMA_Init(DMA0);
    DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);
    DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
}

void DAC_Write(int i)
{
	LOG_DEBUG("DAC_Write\n");
	DAC_SetBufferValue(DAC0, 0U, sin_lookup_table_uint16[i]);
}

void ADC_Read(int i)
{
	LOG_DEBUG("ADC_Read\n");
	g_Adc16ConversionDoneFlag = false;
	ADC16_SetChannelConfig(ADC0, DEMO_ADC16_CHANNEL_GROUP, &g_adc16ChannelConfigStruct);

	while (!g_Adc16ConversionDoneFlag);
	ADC_buf[i] = g_Adc16ConversionValue;
}

void DMA_Transfer(void)
{
	LOG_DEBUG("DMA_Transfer\n");
	DMA_start_time = timerGetRunTimeHundredmsec();
    dma_transfer_config_t transferConfig;
    DMA_PrepareTransfer(&transferConfig, ADC_buf, sizeof(ADC_buf[0]),
    		DSP_buf, sizeof(DSP_buf[0]), sizeof(ADC_buf), kDMA_MemoryToMemory);
    DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
    DMA_StartTransfer(&g_DMA_Handle);
    while (g_Transfer_Done != true);
    DMA_end_time = timerGetRunTimeHundredmsec();
}

void DSP_Summary(uint8_t round_count)
{
	PRINTF("DSP Summary Report %d\t \n",round_count);


	uint16_t DSP_ave = average(DSP_buf, BUF_SIZE);
	uint16_t DSP_max = max(DSP_buf, BUF_SIZE);
	uint16_t DSP_min = min(DSP_buf, BUF_SIZE);
	uint16_t standard_deviation = SD(DSP_buf,DSP_ave,BUF_SIZE);

	float DSP_ave_f = 3.3/4096*DSP_ave;
	float DSP_max_f = 3.3/4096*DSP_max;
	float DSP_min_f = 3.3/4096*DSP_min;
	float standard_deviation_f = 3.3/4096*standard_deviation;
	PRINTF("Ave\t\tMax\t\tMin\t\tSD\t\t \n");
	PRINTF("%f\t%f\t%f\t%f\t \n",DSP_ave_f,DSP_max_f,DSP_min_f,standard_deviation_f);

	PRINTF("\t \n");
}
