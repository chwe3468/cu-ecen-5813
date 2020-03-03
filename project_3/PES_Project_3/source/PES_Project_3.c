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
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "memory_utility.h"


/********************** Define ***********************/

//#define COMMAND_VERSION


/********************** Main ***********************/

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello, PES Project 3\n");

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
	//Allocate a 32 byte region in the heap
	//Verify that memory is allocated (True)
	//Write a pattern using the seed 143 to the first 32 bytes of the allocated memory
	//Display the first 32 bytes of allocated memory
	//Display the first 34 bytes of allocated memory (Out of range error)
	//Compare the first 32 bytes of allocated memory to the pattern with seed 143 (True)
	//Write the hex value 0xFFEE to 2 bytes of allocated memory starting at byte 12
	//Display the first 32 bytes of allocated memory
	//Compare the first 32 bytes of allocated memory to the pattern with seed 143 (False)
	//Write a pattern using the seed 127 to the first 16 bytes of the allocated memory
	//Display the first 16 bytes of allocated memory
	//Compare the first 16 bytes of allocated memory to the pattern with seed 127 (True)
	//Invert all bits in 2 bytes of allocated memory starting at byte 35 (Out of range error)
	//Invert all bits in 2 bytes of allocated memory starting at byte 9
	//Display the first 16 bytes of allocated memory
	//Compare the first 16 bytes of allocated memory to the pattern with seed 127 (False)
	//Invert all bits in 2 bytes of allocated memory starting at byte 9
	//Compare the first 16 bytes of allocated memory to the pattern with seed 127 (True)
	//Display the first 16 bytes of allocated memory
	//Free the allocated memory in the heap
	//Verify that memory is allocated (False)
	while(1)
	{
		//wait for input

	}
#endif
	return 0;
}
