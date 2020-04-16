/*
 * gpio.h
 *
 *  Created on: Feb 11, 2020
 *      Author: chutao
 */

#ifndef GPIO_H_
#define GPIO_H_
/********************** Include ***********************/

#include <stdint.h>
#include "gpio.h"
#include "MKL25Z4.h"

/********************** Typedef ***********************/

/* Enum for pin direction */
typedef enum _gpio_pin_direct
{
	GPIO_DigitalInput = 0U,
	GPIO_DigitalOutput = 1U
}gpio_pin_direct_t;


/********************** Prototype ***********************/

/*************************************************
 * @brief
 *   Initialize GPIO pin's direction and value
 *   (in case if output is selected as direction)
 ************************************************/
void init_GPIO_Pin(GPIO_Type *base, uint32_t pin,
		gpio_pin_direct_t pin_direction, uint8_t pin_data);


/*************************************************
 * @brief
 *   Set Pin to output 1
 ************************************************/
void set_GPIO_Pinout(GPIO_Type *base, uint32_t pin);


/*************************************************
 * @brief
 *   Clear Pin to output 0
 ************************************************/
void clear_GPIO_Pinout(GPIO_Type *base, uint32_t pin);


/*************************************************
 * @brief
 *   Toggle Pin output
 ************************************************/
void toggle_GPIO_Pinout(GPIO_Type *base, uint32_t pin);



#endif /* GPIO_H_ */
