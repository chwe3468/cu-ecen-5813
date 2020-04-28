/*
 * dac_adc.c
 *
 *  Created on: Apr 27, 2020
 *      Author: chutao
 */

#include "dac_adc.h"
#include "fsl_dac.h"
#include "fsl_adc16.h"
#include "fsl_debug_console.h"
#include "MKL25Z4.h"
#include "sin.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL 0U /* PTE20, ADC0_SE0 */
#define NUM_POINTS 50
/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_Adc16ConversionDoneFlag = false;
volatile uint32_t g_Adc16ConversionValue = 0;
adc16_channel_config_t g_adc16ChannelConfigStruct;
uint16_t DAC_result[NUM_POINTS];
/*******************************************************************************
 * Code
 ******************************************************************************/
// code provided by the fsl library

// interrupt hanlder
void ADC0_IRQHandler(void)
{
    g_Adc16ConversionDoneFlag = true;
    /* Read conversion result to clear the conversion completed flag. */
    g_Adc16ConversionValue = ADC16_GetChannelConversionValue(ADC0, DEMO_ADC16_CHANNEL_GROUP);
}

// init function
void DAC_ADC_Init(void)
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
        PRINTF("\r\nADC16_DoAutoCalibration() Done.");
    }
    else
    {
        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

    /* Prepare ADC channel setting */
    g_adc16ChannelConfigStruct.channelNumber = DEMO_ADC16_USER_CHANNEL;
    g_adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = true;

#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    g_adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */
}

void DAC_Write(int i)
{
	DAC_SetBufferValue(DAC0, 0U, sin_lookup_table_uint16[i]);
}

void ADC_Read(int i)
{
	g_Adc16ConversionDoneFlag = false;
	ADC16_SetChannelConfig(ADC0, DEMO_ADC16_CHANNEL_GROUP, &g_adc16ChannelConfigStruct);

	while (!g_Adc16ConversionDoneFlag);
	DAC_result[i] = g_Adc16ConversionValue;
}
void summary_Print(void)
{
	PRINTF("DAC value\t ADC value\t \n");
	int i;
	for (i=0;i<NUM_POINTS;i++)
	{
		PRINTF("%d\t %d\t \n",sin_lookup_table_uint16[i],DAC_result[i]);
	}

}
