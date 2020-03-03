/*
 * led.c
 *
 *  Created on: Feb 11, 2020
 *      Author: chutao
 */


/*************** Include *****************/

#include <stdint.h>
#include "gpio.h"
#include "led.h"
#include "timer.h"
#include "touch_sen.h"
#include "log.h"


/*************** Global Varibles *****************/

led_color_t color = red;
const char * led_color_string[3] ={"on","off","toggle"};


/*************** Function *****************/

void init_LED(void)
{
	init_GPIO_Pin(LED3_RED_PORT,	LED3_RED_PIN,	GPIO_DigitalOutput, 1);
	init_GPIO_Pin(LED3_GREEN_PORT,	LED3_GREEN_PIN,	GPIO_DigitalOutput, 1);
	init_GPIO_Pin(LED3_BLUE_PORT,	LED3_BLUE_PIN,	GPIO_DigitalOutput, 1);
}

void turn_LED_project2_parrtern(void)
{
	// Declare pattern
	uint32_t pattern[8] = {500, 500, 1000, 500, 2000, 500, 3000, 500};

	uint32_t i = 0;
	for(i=0; i<8; i++)
	{
		// Can only change color if loop count is even
		if (!(i&0x1))
		{
			// change the LED color is touched
			change_LED_color(Touch_Scan_Position());
		}
		// toggle LED
		turn_LED(toggle);
		// delay for a while
		delay_ms(pattern[i]);
	}
}

void turn_LED(led_state_t LED_state)
{
	if (color == red)
	{
		turn_LED_red(LED_state);
	}
	else if (color == green)
	{
		turn_LED_green(LED_state);
	}
	else if (color == blue)
	{
		turn_LED_blue(LED_state);
	}
	else
	{
		LOG_ERROR("Unexpected led_state_t");
	}
}

void change_LED_color(led_color_t LED_color)
{
	color = LED_color;
}

void turn_LED_red(led_state_t LED_state)
{
	LOG_DEBUG("Turn LED red %s",led_color_string[LED_state]);
	color = red;
	if (LED_state == off)
	{
		set_GPIO_Pinout(LED3_RED_PORT, LED3_RED_PIN);
	}
	else if (LED_state == on)
	{
		clear_GPIO_Pinout(LED3_RED_PORT, LED3_RED_PIN);
	}
	else if (LED_state == toggle)
	{
		toggle_GPIO_Pinout(LED3_RED_PORT, LED3_RED_PIN);
	}
	else
	{
		LOG_ERROR("Unexpected led_state_t");
	}
}

void turn_LED_green(led_state_t LED_state)
{
	LOG_DEBUG("Turn LED green %s",led_color_string[LED_state]);
	color = green;
	if (LED_state == off)
	{
		set_GPIO_Pinout(LED3_GREEN_PORT, LED3_GREEN_PIN);
	}
	else if (LED_state == on)
	{
		clear_GPIO_Pinout(LED3_GREEN_PORT, LED3_GREEN_PIN);
	}
	else if (LED_state == toggle)
	{
		toggle_GPIO_Pinout(LED3_GREEN_PORT, LED3_GREEN_PIN);
	}
	else
	{
		LOG_ERROR("Unexpected led_state_t");
	}
}

void turn_LED_blue(led_state_t LED_state)
{
	LOG_DEBUG("Turn LED blue %s",led_color_string[LED_state]);
	color = blue;
	if (LED_state == off)
	{
		set_GPIO_Pinout(LED3_BLUE_PORT, LED3_BLUE_PIN);
	}
	else if (LED_state == on)
	{
		clear_GPIO_Pinout(LED3_BLUE_PORT, LED3_BLUE_PIN);
	}
	else if (LED_state == toggle)
	{
		toggle_GPIO_Pinout(LED3_BLUE_PORT, LED3_BLUE_PIN);
	}
	else
	{
		LOG_ERROR("Unexpected led_state_t");
	}
}