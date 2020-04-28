/*
 * sin.c
 *
 *  Created on: Apr 26, 2020
 *      Author: user
 */

#include <stdint.h>
#include <math.h>
#include "sin.h"
// float version
#define PI 3.14159265358979323846
double sin_lookup_table[NUM_POINTS];

void init_table(){
	double increment=2*PI/50;
	double d=0;
	for(int i=0; i<NUM_POINTS; i++){
		sin_lookup_table[i]=sin(d)+2;
		d=d+increment;
	}
}


#define ONE_VOLT_FLOAT 		1241.21
#define THREE_VOLT_FLOAT 	3723.64
#define AVERAGE_VOLT		((ONE_VOLT_FLOAT+THREE_VOLT_FLOAT)/2)
#define HALF_PEAK_TO_PEAK	((THREE_VOLT_FLOAT-ONE_VOLT_FLOAT)/2)
#define PI 3.14159265358979323846

// int16 version
uint16_t sin_lookup_table_uint16[NUM_POINTS];
void init_table_uint16()
{
	double increment=2*PI/50;
	double d=0;
	for(int i=0; i<NUM_POINTS; i++){
		sin_lookup_table_uint16[i]=(uint16_t)(HALF_PEAK_TO_PEAK*sin(d)+AVERAGE_VOLT);
		d=d+increment;
	}
}
