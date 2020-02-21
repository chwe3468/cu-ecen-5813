/*
 * led.h
 *
 *  Created on: Feb 11, 2020
 *      Author: chutao
 */

#ifndef LED_H_
#define LED_H_

/*************** Include *****************/

#include <stdint.h>
#include "MKL25Z4.h"

/*************** Define *****************/

#define LED3_RED_PORT	(GPIOB)
#define LED3_GREEN_PORT	(GPIOB)
#define LED3_BLUE_PORT	(GPIOD)
#define LED3_RED_PIN	(18U)
#define LED3_GREEN_PIN	(19U)
#define LED3_BLUE_PIN	(1U)

/********************** Typedef ***********************/

/* enum for pin config */
typedef enum _led_state
{
	off = 0U,
	on = 1U,
	toggle = 2U
}led_state_t;

/* enum for pin config */
typedef enum _led_color
{
	red = 0U,
	green = 1U,
	blue = 2U
}led_color_t;

/*************** Prototype *****************/

/*************************************************
 * @brief
 *   Initialize RGB LED to output direction
 ************************************************/
void init_LED(void);


/*************************************************
 * @brief
 *   Turn LED on/off using pattern specified in
 *   PES project 2.pdf
 ************************************************/
void turn_LED_project2_pattern(void);


/*************************************************
 * @brief
 *   Turn LED either on/off/toggle, the color
 *   depends on the state variable "color" defined
 *   in Global Variable section of led.c. If you
 *   want to change color please refer to
 *   change_LED_color() function
 ************************************************/
void turn_LED(led_state_t LED_state);


/*************************************************
 * @brief
 *   Change the state variable "color" defined
 *   in Global Variable section of led.c.
 ************************************************/
void change_LED_color(led_color_t LED_color);


/*************************************************
 * @brief
 *   Turn RGB LED red on/off/toggle
 ************************************************/
void turn_LED_red(led_state_t LED_state);


/*************************************************
 * @brief
 *   Turn RGB LED green on/off/toggle
 ************************************************/
void turn_LED_green(led_state_t LED_state);


/*************************************************
 * @brief
 *   Turn RGB LED blue on/off/toggle
 ************************************************/
void turn_LED_blue(led_state_t LED_state);




#endif /* LED_H_ */
