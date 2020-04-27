/*
 * sin.c
 *
 *  Created on: Apr 26, 2020
 *      Author: user
 */


#include <math.h>
#include "sin.h"

#define PI 3.14159265358979323846

double sin_lookup_table[NUM_POINTS];

void init_table(){
	double increment=PI/50;
	double d=0;
	for(int i=0; i<NUM_POINTS; i++){
		sin_lookup_table[i]=sin(d)+2;
		d=d+increment;
	}
}
