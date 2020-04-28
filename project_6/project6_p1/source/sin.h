/*
 * sin.h
 *
 *  Created on: Apr 26, 2020
 *      Author: user
 */

#ifndef SIN_H_
#define SIN_H_
#define NUM_POINTS 50

extern double sin_lookup_table[NUM_POINTS];
extern uint16_t sin_lookup_table_uint16[NUM_POINTS];

void init_table();
void init_table_uint16();

#endif /* SIN_H_ */
