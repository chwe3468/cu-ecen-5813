/*
 * command_parser.h
 *
 *  Created on: Mar 9, 2020
 *      Author: chutao
 */

#ifndef COMMAND_PARSER_H_
#define COMMAND_PARSER_H_


/********************** Include ***********************/

#include <stdint.h>
#include "MKL25Z4.h"

/********************** Typedef ***********************/


/********************** Prototype ***********************/

/*************************************************
 * @brief
 *   This function echo the user input and count
 *   the charcter they have.
 *
 *   For example:
 *   User_input: "Cha"
 *   output:C – 1; a – 2; h – 1;
 ************************************************/
int command_parser(command_struct_t * user_input);


#endif /* COMMAND_PARSER_H_ */
