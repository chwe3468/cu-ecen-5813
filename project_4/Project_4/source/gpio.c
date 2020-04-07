/*
 * gpio.c
 *
 *  Created on: Feb 11, 2020
 *      Author: chutao
 *
 *  Minic the functions from fsl_gpio.c
 *  Still use MKL25Z4.h for hardware addresses
 */

/********************** Include ***********************/

#include <stdio.h>
#include <stdint.h>
#include "gpio.h"


/********************** Function ***********************/

void set_GPIO_Pinout(GPIO_Type *port, uint32_t pin)
{
	port->PSOR = (0x1 << pin);
}

void clear_GPIO_Pinout(GPIO_Type *port, uint32_t pin)
{
	port->PCOR = (0x1 << pin);
}

void toggle_GPIO_Pinout(GPIO_Type *port, uint32_t pin)
{
	port->PTOR = (0x1 << pin);
}

void init_GPIO_Pin(GPIO_Type *port, uint32_t pin,
		gpio_pin_direct_t pin_direction, uint8_t pin_data)
{
	if (pin_direction == GPIO_DigitalInput)
	{
		// Set pin to input direction
		port->PDDR &= ~(0x1 << pin);
	}
	else if (pin_direction == GPIO_DigitalOutput)
	{
		// Set pin to output direction
		port->PDDR |= (0x1 << pin);
		if (pin_data)
		{
			set_GPIO_Pinout(port,pin);
		}
		else
		{
			clear_GPIO_Pinout(port,pin);
		}
	}
	else
	{
#ifdef LOGGING_DEBUG
		// TODO: Debug message
#endif
	}
}
