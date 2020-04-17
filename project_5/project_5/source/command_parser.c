/*
 * command_parser.c
 *
 *  Created on: Mar 9, 2020
 *      Author: Curry
 */

/********************** Include ***********************/

#include "command_parser.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/********************** Define ***********************/
#define MAX_USER_BUF 64
#define MAX_USER_ARG 4



/********************** Function ***********************/
int command_parser (command_struct_t * user_input)
{
	// Initialize char array
	char str[MAX_USER_BUF];

	int i=0;
	//takes all the characters until enter is pressed
	while((str[i]=getchar())!='\n'){
		//increment the index of the character array
		i++;
		// protect against long input
		if(i == MAX_USER_BUF-1)
		{
		    str[MAX_USER_BUF-1] = '\0';
		}
	}


	int arg_index = 0;
	uint32_t hex = 0;
    char * pch[MAX_USER_ARG];
    /* Split User input string  */
    pch[arg_index] = strtok (str," ,");
    while (pch[arg_index] != NULL)
    {
        //printf ("%s\n",pch[arg_index]);
    	switch (arg_index)
        {
            case 0:
                user_input->command = pch[arg_index][0];
                break;
            case 1:
                user_input->num_bytes = atoi(pch[arg_index]);
                break;
            case 2:
                user_input->offset = atoi(pch[arg_index]);
                break;
            case 3:
                sscanf(pch[arg_index], "%x", &hex);
                user_input->hex_value = hex;
                break;
            default:
                printf("error state in command parser\n");
                break;
        }
        // do the next argument
        arg_index++;
        pch[arg_index] = strtok (NULL, " ,");
    }

    return arg_index;
}
