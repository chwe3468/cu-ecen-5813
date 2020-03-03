/*
 * pattern_gen.c
 *
 *  Created on: Mar 1, 2020
 *      Author: Wikipedia
 *      Editor: Chutao Wei
 *      Source: https://en.wikipedia.org/wiki/Linear-feedback_shift_register
 */


# include <stdint.h>

uint8_t lfsr8bit(uint8_t num_shift)
{
	// initialize lfsr value
	uint8_t lfsr = 0xFF;  // Any nonzero start state will work.
	// loop variable
    uint8_t index = 0;
    // the new bit added to the byte
    uint8_t bit = 0;
    for(index=0;index<num_shift;index++)
    {
    	// formula for maximum shift count
    	bit = ((lfsr << 7) ^ (lfsr << 5) ^ (lfsr << 4) ^ (lfsr << 3)) ^ 1 /* & 1u */;
    	// new lfsr value
    	lfsr = (lfsr << 1) | (bit >> 7);
    }
    return lfsr;
}


void pattern_gen(uint8_t num_bytes, uint8_t array[], uint8_t seed)
{
	// number of shift
	uint8_t num_shift = seed;
	// loop variable
	uint8_t index;
    for(index=0;index<num_bytes;index++)
    {
    	array[index] = lfsr8bit(num_shift);
    	num_shift++;
    }
}
