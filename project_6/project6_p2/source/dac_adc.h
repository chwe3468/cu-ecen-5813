/*
 * dac_adc.h
 *
 *  Created on: Apr 27, 2020
 *      Author: chutao
 */

#ifndef DAC_ADC_H_
#define DAC_ADC_H_

void DAC_ADC_DMA_Init(void);
void DAC_Write(int i);
void ADC_Read(int i);
void DMA_Transfer(void);
void DSP_Summary(uint8_t round_count);



#endif /* DAC_ADC_H_ */
