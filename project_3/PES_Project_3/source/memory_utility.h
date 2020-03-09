/*
 * memory_utility.h
 *
 *  Created on: Mar 1, 2020
 *      Author: chutao
 */

#ifndef MEMORY_UTILITY_H_
#define MEMORY_UTILITY_H_


/*************** Include *****************/

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pattern_gen.h"


/*************** Structure *****************/

typedef struct mem_record
{
	void* pointer;
	size_t num_bytes;
}mem_record_t;

/*************** Enumeration *****************/

typedef enum mem_status
{
	SUCCESS = 0, // no error
	FAILED = 1// failure case
}mem_status_t;


/*************** Prototype *****************/

/*************************************************
 * @brief
 *   Allocate (size_t num_bytes) using malloc
 ************************************************/
void * allocate_bytes(size_t num_bytes);

/*************************************************
 * @brief
 *   Free allocated memory at address pointed by
 *   (void * data)
 ************************************************/
mem_status_t free_allocated(void * data);

/*************************************************
 * @brief
 *   Verify the memory is for testing is
 *   available. This function only check if the
 *   void * data is allocated using
 *   allocate_bytes() function. If it is used by
 *   malloc directly, it will return false. It
 *   only verify the pointer, not not many bytes.
 ************************************************/
mem_status_t verify_memory(void * data);

/*************************************************
 * @brief
 *   Print out the memory content starting at
 *   addr. Each line follows by address, hex
 *   value, BIT31~24, BIT23~16, BIT15~8, BIT7~0.
 *   No pointer would be given by
 ************************************************/
mem_status_t display_memory(void * data, size_t num_bytes);

/*************************************************
 * @brief
 *   Write address+offset with bytes
 ************************************************/
mem_status_t write_memory(void * data, uint8_t offset,
		size_t num_bytes, uint8_t * bytes);

/*************************************************
 * @brief
 *   Invert all bits in a memory region
 ************************************************/
mem_status_t invert_block(void * data, uint8_t offset,
		size_t num_bytes);

/*************************************************
 * @brief
 *   Write num_bytes of random bytes to location
 *   pointed by void * data.
 * @note
 *   This function uses pattern_gen() function
 *   Please include pattern_gen.h in order to
 *   use the function
 ************************************************/
mem_status_t write_pattern(void * data, uint8_t offset,
		size_t num_bytes, uint8_t seed);

/*************************************************
 * @brief
 *   Compare the array stored in memory with the
 *   array generated by the seed value. Both of
 *   them should be the same if the array stored
 *   in memory uses the same seed value.
 ************************************************/
mem_status_t compare_pattern(void * data, uint8_t offset,
		size_t num_bytes, uint8_t seed);


#endif /* MEMORY_UTILITY_H_ */
