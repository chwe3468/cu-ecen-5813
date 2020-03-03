/*
 * pattern_gen.h
 *
 *  Created on: Mar 1, 2020
 *      Author: chutao
 */

#ifndef PATTERN_GEN_H_
#define PATTERN_GEN_H_

/*************** Include *****************/

#include <stdint.h>


/*************** Prototype *****************/

/*************************************************
 * @brief
 *   Write num_bytes of random bytes to location
 *   pointed by void * data.
 * @note
 *   This function uses pattern_gen() function
 *   Please include pattern_gen.h in order to
 *   use the function
 ************************************************/
void pattern_gen(uint8_t num_bytes, uint8_t * bytes,
		uint8_t seed);


#endif /* PATTERN_GEN_H_ */
