/*
 * display_memory.c
 *
 *  Created on: Feb 25, 2020
 *      Author: Chutao
 */


/*************** Include *****************/

#include <stdint.h>
#include <stdio.h>
#include "memory_utility.h"

/*************** Define *****************/
// the following binary pattern code is quoted from William Whyte
// and edited a little bit by me
// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format?page=1&tab=votes#tab-top

#define BYTE_TO_BINARY_PATTERN "0b%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#define MAX_RECORD 10


/*************** Global *****************/

int current_mem_index=-1;
mem_record_t mem_record[MAX_RECORD]={{NULL},{0}};


/*************** Function *****************/

mem_status_t check_allocated_bound(
		void * pointer, uint8_t offset, size_t num_bytes)
{
	if(pointer == NULL)
	{
		return FAILED;
	}
	int index;
	for(index=0;index<MAX_RECORD;index++)
	{
		if(mem_record[index].pointer == pointer)
			if(mem_record[index].num_bytes >=
					num_bytes+offset)
				return SUCCESS;
	}

	return FAILED;
}

mem_status_t check_allocated(
		void * pointer, size_t num_bytes)
{
	if(pointer == NULL)
	{
		return FAILED;
	}
	int index;
	for(index=0;index<MAX_RECORD;index++)
	{
		if(mem_record[index].pointer == pointer)
			if(mem_record[index].num_bytes == num_bytes)
				return SUCCESS;
	}

	return FAILED;
}

mem_status_t add_allocated(
		void * pointer, size_t num_bytes)
{
	if(pointer == NULL)
	{
		return FAILED;
	}
	if(current_mem_index<MAX_RECORD)
	{
		current_mem_index++;
		mem_record[current_mem_index].pointer = pointer;
		mem_record[current_mem_index].num_bytes = num_bytes;
	}
	else
	{
		return FAILED;
	}
	return SUCCESS;
}

mem_status_t remove_allocated(void * pointer)
{
	if(pointer == NULL)
	{
		return FAILED;
	}
	if(current_mem_index>-1)
	{
		mem_record[current_mem_index].pointer = NULL;
		mem_record[current_mem_index].num_bytes = 0;
		current_mem_index--;
	}
	else
	{
		return FAILED;
	}
	return SUCCESS;
}

void * allocate_bytes(size_t num_bytes)
{
	void * pointer = malloc(num_bytes);
	mem_status_t status = add_allocated(pointer, num_bytes);
	if (status == FAILED)
	{
		free(pointer);
	}
	return pointer;
}

mem_status_t free_allocated(void * data)
{
	mem_status_t status = remove_allocated(data);
	if (status == FAILED)
	{
		// TODO print warning
		return FAILED;
	}
	free(data);
	return SUCCESS;
}

mem_status_t verify_memory(void * data)
{
	if(data == NULL)
	{
		return FAILED;
	}
	int index;
	for(index=0;index<MAX_RECORD;index++)
	{
		if(mem_record[index].pointer == data)
			return SUCCESS;
	}

	return FAILED;
}

mem_status_t display_memory(void * data, uint32_t num_bytes)
{
	if (check_allocated_bound(data,0,num_bytes)==FAILED)
	{
		return FAILED;
	}
	// dummy pointer so that we can manipulate this one
    uint32_t * pointer = (uint32_t*) data;
    uint32_t num_4bytes = num_bytes/4+((num_bytes%4)?1:0);
	// Print table first row
	printf("Address\t\tHex Value\tBIT31~24\tBIT23~16\tBIT15~8\t\tBIT7~0\t\n");

	// loop variable
	int index = 0;
	int byte_index = 0;
	// Print Table other rows
	for (index=0; index<num_4bytes; index++)
	{
		// Print address and hex value
		printf("0x%08X\t0x%08X\t",
		    (uint32_t)pointer,
		    *pointer);

		// Print bytes from MSB to LSB
		for (byte_index=3; byte_index>=0; byte_index--)
		{
			printf(BYTE_TO_BINARY_PATTERN"\t",
				BYTE_TO_BINARY(*(((uint8_t *) pointer)+byte_index)));

		}
		printf("\n");
		pointer = ((uint32_t *)pointer)+1;

	}
	return SUCCESS;
}

mem_status_t write_memory(void * data, uint8_t offset,
		size_t num_bytes, uint8_t * bytes)
{
	if (check_allocated_bound(data, offset, num_bytes)==FAILED)
	{
		return FAILED;
	}
	// dummy pointer so that we can manipulate this one
    uint8_t * pointer = (uint8_t*) (data + offset);

	// loop variable
	int index = 0;

	// write all bytes to pointed location
    for(index=0; index<num_bytes;index++)
    {
    	pointer[index] = bytes[index];
    }
    return SUCCESS;
}

mem_status_t invert_block(void * data, uint8_t offset,
		size_t num_bytes)
{
	if (check_allocated_bound(data, offset, num_bytes)==FAILED)
	{
		return FAILED;
	}
	// dummy pointer so that we can manipulate this one
    uint8_t * pointer = (uint8_t*) (data + offset);

	// loop variable
	int index = 0;

	// write all bytes to pointed location
    for(index=0; index<num_bytes;index++)
    {
    	pointer[index] = (pointer[index]^0xFF);
    }
    return SUCCESS;
}

mem_status_t write_pattern(void * data, uint8_t offset,
		size_t num_bytes, uint8_t seed)
{
	if (check_allocated_bound(data, offset, num_bytes)==FAILED)
	{
		return FAILED;
	}
	// create a randomized uint8_t array;
	uint8_t array[num_bytes];
	pattern_gen(num_bytes, array, seed);

	// dummy pointer so that we can manipulate this one
    uint8_t * pointer = (uint8_t*) (data + offset);

	// loop variable
	int index = 0;

	// write all bytes to pointed location
    for(index=0; index<num_bytes;index++)
    {
    	pointer[index] = array[index];
    }
    return SUCCESS;
}

mem_status_t compare_pattern(void * data, uint8_t offset,
		size_t num_bytes, uint8_t seed)
{
	if (check_allocated_bound(data, offset, num_bytes)==FAILED)
	{
		return FAILED;
	}
	// create a randomized uint8_t array;
	uint8_t array[num_bytes];
	pattern_gen(num_bytes, array,
			seed);

	// dummy pointer so that we can manipulate this one
    uint8_t * pointer = (uint8_t*) (data + offset);

	// loop variable
	int index = 0;

	// write all bytes to pointed location
    for(index=0; index<num_bytes;index++)
    {
    	if(pointer[index] != array[index])
		{
    		return FAILED;
		}

    }
    return SUCCESS;
}
