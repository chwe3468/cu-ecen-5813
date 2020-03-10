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

/* Typedef for Command Struct */
typedef struct command_struct
{
	char command;
	size_t num_bytes;
	union{
		uint8_t offset;
		uint8_t seed;
	};
	uint32_t hex_value;
}command_struct_t;


/********************** Prototype ***********************/

/*************************************************
 * @brief
 *   This function takes user input in command
 *   line format.
 *   The user input should be in the
 *   following format:
 *   command, num_bytes, offset/seed, hex_value
 *
 *   For example:
 *   W,12,2,0xFFEE is: Write the hex value 0xFFEE
 *   to 2 bytes of allocated memory starting at
 *   byte 12
 * @return
 *   Number of user inputs separated my comma
 ************************************************/
int command_parser(command_struct_t * user_input);


#endif /* COMMAND_PARSER_H_ */
