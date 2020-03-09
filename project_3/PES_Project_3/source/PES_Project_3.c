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
 * @file    PES_Project_3.c
 * @brief   Application entry point.
 */

/********************** Include ***********************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "memory_utility.h"
#include "command_parser.h"
#include "led.h"
#include "timer.h"

/********************** Define ***********************/

#define COMMAND_VERSION
//#define BUTTON
#ifdef BUTTON
#define PRESS printf("press ENTER to continue");getchar()
#else
#define PRESS printf("\n")
#endif


/********************** Main ***********************/

typedef union {
  void * (*allocate_bytes)(size_t num_bytes);
  mem_status_t (*free_allocated)(void * data);
  mem_status_t (*verify_memory)(void * data);
  mem_status_t (*display_memory)(void * data, size_t num_bytes);
  mem_status_t (*write_memory)(void * data, uint8_t offset,
			size_t num_bytes, uint8_t * bytes);
  mem_status_t (*invert_block)(void * data, uint8_t offset,
			size_t num_bytes);
  mem_status_t (*write_pattern)(void * data, uint8_t offset,
			size_t num_bytes, uint8_t seed);
  mem_status_t (*compare_pattern)(void * data, uint8_t offset,
			size_t num_bytes, uint8_t seed);
} cmd_func;


/********************** Main ***********************/

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    init_LED();
    PRINTF("Hello, PES Project 3\n");

    // turn LED blue before start the test
	turn_LED_blue(toggle);
	delay_ms(500);
	turn_LED_blue(toggle);
	delay_ms(500);
#ifndef COMMAND_VERSION
    int num_FAILED = 0;
	//Allocate a 32 byte region in the heap
	void * xxx = allocate_bytes(32);
	//Verify that memory is allocated (True)
	mem_status_t status = verify_memory(xxx);
	if (status == FAILED)
	{
		printf("verify_memory failed\n");
		num_FAILED++;
	}
	//Write a pattern using the seed 143 to the first 32 bytes of the allocated memory
	status = write_pattern(xxx, 0, 32, 143);
	if (status == FAILED)
	{
		printf("write_pattern failed\n");
		num_FAILED++;
	}
	//Display the first 32 bytes of allocated memory
	status = display_memory(xxx, 32);
	if (status == FAILED)
	{
		printf("display_memory failed\n");
		num_FAILED++;
	}
	//Display the first 34 bytes of allocated memory (Out of range error)
	status = display_memory(xxx, 34);
	if (status == FAILED)
	{
		printf("display_memory failed\n");
		num_FAILED++;
	}
	//Compare the first 32 bytes of allocated memory to the pattern with seed 143 (True)
	status = compare_pattern(xxx, 0, 32, 143);
	if (status == FAILED)
	{
		printf("compare_pattern failed\n");
		num_FAILED++;
	}
	//Write the hex value 0xFFEE to 2 bytes of allocated memory starting at byte 12
	uint8_t array[] = {0xFF,0xEE};
	status = write_memory(xxx, 12, 32, array);
	if (status == FAILED)
	{
		printf("write_memory failed\n");
		num_FAILED++;
	}
	//Display the first 32 bytes of allocated memory
	status = display_memory(xxx, 32);
	if (status == FAILED)
	{
		printf("display_memory failed\n");
		num_FAILED++;
	}
	//Compare the first 32 bytes of allocated memory to the pattern with seed 143 (False)
	status = compare_pattern(xxx, 0, 32, 143);
	if (status == FAILED)
	{
		printf("compare_pattern failed\n");
		num_FAILED++;
	}
	//Write a pattern using the seed 127 to the first 16 bytes of the allocated memory
	status = write_pattern(xxx, 0, 16, 127);
	if (status == FAILED)
	{
		printf("write_pattern failed\n");
		num_FAILED++;
	}
	//Display the first 16 bytes of allocated memory
	status = display_memory(xxx, 16);
	if (status == FAILED)
	{
		printf("display_memory failed\n");
		num_FAILED++;
	}
	//Compare the first 16 bytes of allocated memory to the pattern with seed 127 (True)
	status = compare_pattern(xxx, 0, 16, 127);
	if (status == FAILED)
	{
		printf("compare_pattern failed\n");
		num_FAILED++;
	}
	//Invert all bits in 2 bytes of allocated memory starting at byte 35 (Out of range error)
	status = invert_block(xxx, 35, 2);
	if (status == FAILED)
	{
		printf("invert_block failed\n");
		num_FAILED++;
	}
	//Invert all bits in 2 bytes of allocated memory starting at byte 9
	status = invert_block(xxx, 9, 2);
	if (status == FAILED)
	{
		printf("invert_block failed\n");
		num_FAILED++;
	}
	//Display the first 16 bytes of allocated memory
	status = display_memory(xxx, 16);
	if (status == FAILED)
	{
		printf("display_memory failed\n");
		num_FAILED++;
	}
	//Compare the first 16 bytes of allocated memory to the pattern with seed 127 (False)
	status = compare_pattern(xxx, 0, 16, 127);
	if (status == FAILED)
	{
		printf("compare_pattern failed\n");
		num_FAILED++;
	}
	//Invert all bits in 2 bytes of allocated memory starting at byte 9
	status = invert_block(xxx, 9, 2);
	if (status == FAILED)
	{
		printf("invert_block failed\n");
		num_FAILED++;
	}
	//Compare the first 16 bytes of allocated memory to the pattern with seed 127 (True)
	status = compare_pattern(xxx, 0, 16, 127);
	if (status == FAILED)
	{
		printf("compare_pattern failed\n");
		num_FAILED++;
	}
	//Display the first 16 bytes of allocated memory
	status = display_memory(xxx, 16);
	if (status == FAILED)
	{
		printf("display_memory failed\n");
		num_FAILED++;
	}
	//Free the allocated memory in the heap
	status = free_allocated(xxx);
	if (status == FAILED)
	{
		printf("free_allocated failed\n");
		num_FAILED++;
	}
	//Verify that memory is allocated (False)
	status = verify_memory(xxx);
	if (status == FAILED)
	{
		printf("verify_memory failed\n");
		num_FAILED++;
	}

	// Check if num_FAILED is correct
	if (num_FAILED == 5)
	{
		printf("Test Pass!");
	}
#endif

#ifdef COMMAND_VERSION
	while (1)
	{

		command_struct_t user_input;
		command_parser(&user_input);

		cmd_func cmd;
		void * xxx;
		mem_status_t error=SUCCESS;

		uint8_t hex_bytes[4];
		hex_bytes[0] = user_input.hex_value;
		hex_bytes[1] = user_input.hex_value>>8;
		hex_bytes[2] = user_input.hex_value>>16;
		hex_bytes[3] = user_input.hex_value>>24;

		switch (user_input.command)
		{
			case 'a':
			case 'A':
				cmd.allocate_bytes=&allocate_bytes;
				PRESS;
				xxx = (cmd.allocate_bytes(user_input.num_bytes));
				if(xxx == NULL)
				{
					error=FAILED;
				}
				break;
			case 'f':
			case 'F':
				cmd.free_allocated=&free_allocated;
				PRESS;
				error = (cmd.free_allocated(xxx));
				break;
			case 'm':
			case 'M':
				cmd.verify_memory=&verify_memory;
				PRESS;
				error = (cmd.verify_memory(xxx));
				break;
			case 'd':
			case 'D':
				cmd.display_memory=&display_memory;
				//PRESS;
				error = (cmd.display_memory(xxx, user_input.num_bytes));
				break;
			case 'w':
			case 'W':
				cmd.write_memory=&write_memory;
				PRESS;
				error = (cmd.write_memory(
						xxx,
						user_input.offset,
						user_input.num_bytes,
						hex_bytes));
				break;
			case 'i':
			case 'I':
				cmd.invert_block=&invert_block;
				PRESS;
				error = (cmd.invert_block(
						xxx,
						user_input.offset,
						user_input.num_bytes));
				break;
			case 'p':
			case 'P':
				cmd.write_pattern=&write_pattern;
				PRESS;
				error = (cmd.write_pattern(
						xxx,
						0,
						user_input.num_bytes,
						user_input.seed));
				break;
			case 'c':
			case 'C':
				cmd.compare_pattern=&compare_pattern;
				PRESS;
				error = (cmd.compare_pattern(
						xxx,
						0,
						user_input.num_bytes,
						user_input.seed));
				break;
			default: // code to be executed if n doesn't match any cases
				printf("invalid command\n");
		}
		if (error)
		{
			turn_LED_red(toggle);
			delay_ms(500);
			turn_LED_red(toggle);
			delay_ms(500);
		}
		else
		{
			turn_LED_green(toggle);
			delay_ms(500);
			turn_LED_green(toggle);
			delay_ms(500);
		}
	}

#endif
	return 0;
}
