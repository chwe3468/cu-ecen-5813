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
  mem_status_t (*display_memory)(void * data, uint32_t num_bytes);
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
    size_t bufsize = 32;
    //size_t len;
    char *line = (char *)malloc(bufsize * sizeof(char));
    char *p=line;
    // Initialize Input Line String pointer
    //char * line = (char*)malloc( 65 * sizeof(char) );
    char *command = (char*)malloc( 5 * sizeof(char) );
    char *arg1 = (char*)malloc( 5 * sizeof(char) );
    char *arg2 = (char*)malloc( 5 * sizeof(char) );
    char *arg3 = (char*)malloc( 50 * sizeof(char) );
    char *args[4]={command, arg1, arg2, arg3};
    while (args[0][0]!='Q') {
        //printf("%d|%s",len,line);
        p=line;
        while((*p++ = getchar())!= '\n');
        *p = '\0';
        int comma_count=0;
        int i=0;
        while(line[i]){
            if (line[i]==',' || line[i]=='\n' || line[i]=='\0'){
                strncpy(args[comma_count], line,i);
                comma_count=(comma_count+1)%4;
                if (line[i]!='\n' || line[i]!='\0'){
                    line=line+i+1;
                    i=0;
                }
            }
            i++;
        }        printf("\n--%s,%s,%s,%s--\n",args[0],args[1],args[2],args[3]);
        //cmd_func cmd;        printf("args[0] is %s",args[1]);
        switch (args[0][0])
        {
            case 'a':
            case 'A': // code to be executed if n = 1;
                //cmd.allocate_bytes=&my_allocate_bytes;
            	PRESS;
                //xxx=*cmd.allocate_bytes(args[1]);
                break;
            case 'f':
            case 'F': // code to be executed if n = 2;
                //cmd.free_allocated=&my_free_allocated;
                PRESS;
                //*cmd.free_allocated(xxx);
                break;
            case 'm':
            case 'M': // code to be executed if n = 1;
                //cmd.verify_memory=&my_verify_memory;
                PRESS;
                //*cmd.verify_memory(xxx);
                break;
            case 'd':
            case 'D': // code to be executed if n = 2;
                //cmd.display_memory=&my_display_memory;
                PRESS;
                //*cmd.display_memory(xxx,args[1]);
                break;
            case 'w':
            case 'W': // code to be executed if n = 1;
                //cmd.write_memory=&my_write_memory;
                PRESS;
                uint8_t *hex;
                sscanf(args[3], "%x", hex);
                //*cmd.write_memory(xxx,args[1],args[2], hex);
                break;
            case 'i':
            case 'I': // code to be executed if n = 2;
                //cmd.invert_block=&my_invert_block;
                PRESS;
                //*cmd.invert_block(xxx,args[1],args[2]);
                break;
            case 'p':
            case 'P': // code to be executed if n = 2;
                //cmd.write_pattern=&my_write_pattern;
                printf("press ENTER to continue\n");
                getchar(); //wait for enter to continue to next line
                //*cmd.write_pattern(xxx,args[1],args[2]);
                break;
            case 'c':
            case 'C': // code to be executed if n = 2;
                //cmd.compare_pattern=&my_compare_pattern;
                PRESS;
                //*cmd.compare_pattern(xxx,args[1],args[2]);
                break;
            default: // code to be executed if n doesn't match any cases
                printf("invalid command\n");
        }
        memset(command,'\0',5);
        memset(arg1,'\0',5);
        memset(arg2,'\0',5);
        memset(arg3,'\0',50);
    }
    if (line)
        free(line);
    if (command)
        free(command);
    if (arg1)
        free(arg1);
    if (arg2)
        free(arg2);
    if (arg3)
        free(arg3);
#endif
	return 0;
}
