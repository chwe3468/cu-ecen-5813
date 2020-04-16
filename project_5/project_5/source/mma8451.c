/*
 * mma8451.c
 *
 *  Created on: Apr 1, 2020
 *      Author: user
 */
//adapted from https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/

/*************** Include *****************/

#include <MKL25Z4.h>
#include "mma8451.h"
#include "i2c.h"
#include "timer.h"
#include "logger.h"

/*************** Global *****************/
#define MAX_DATA_SET_COUNT	3

/*************** Global *****************/
// data variables
uint32_t data_set_count = 0;
uint32_t current_data_set_num = 0;
int16_t acc_x[MAX_DATA_SET_COUNT]; // syntax for every entry to be 0
int16_t acc_y[MAX_DATA_SET_COUNT];
int16_t acc_z[MAX_DATA_SET_COUNT];


/*************** Function *****************/
int16_t average(int16_t arr[], uint32_t n)
{
    int i;
    int average = arr[0];
    for (i = 0; i < n; i++)
    	average = average + arr[i];
    return (average/n);
}
// source: https://www.geeksforgeeks.org/c-program-find-largest-element-array/
int16_t max(int16_t arr[], uint32_t n)
{
    int i;
    int max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int16_t min(int16_t arr[], uint32_t n)
{
    int i;
    int min = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

int init_mma8451()
{
	// make sure device is connected
	uint8_t whoami_val = 0;
	whoami_val = i2c_read_byte(MMA_ADDR, REG_WHOAMI);
	if (whoami_val != WHOAMI)
	{
		// error, either not connected
		// or corrupted data
		return 1;
	}

	// set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x03);
	return 0;
}

int verify_connect_mma8451()
{
	// make sure device is connected
	uint8_t whoami_val = 0;
	whoami_val = i2c_read_byte(MMA_ADDR, WHOAMI);
	if (whoami_val != 0x1A)
	{
		// error, either not connected
		// or corrupted data
		return 1;
	}

	return 0;
}


void read_full_xyz()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);

	// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0);
	}
	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	// Align for 14 bits
	// assign to the current array
	acc_x[current_data_set_num] = temp[0]>>2;
	acc_y[current_data_set_num] = temp[1]>>2;
	acc_z[current_data_set_num] = temp[2]>>2;

	// update data_set_count
	if (data_set_count != MAX_DATA_SET_COUNT)
		data_set_count ++;

	// update current data_set
	if (current_data_set_num == 2)
		current_data_set_num = 0;
	else if ((data_set_count==1)||(current_data_set_num==0))
		current_data_set_num = current_data_set_num;
	else
		current_data_set_num ++;
}


void read_xyz(void)
{
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	acc_x[current_data_set_num] = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI)<<6;
	mdelay(100);
	acc_y[current_data_set_num] = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI)<<6;
	mdelay(100);
	acc_z[current_data_set_num] = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI)<<6;

	// update data_set_count
	if (data_set_count != MAX_DATA_SET_COUNT)
		data_set_count ++;

	// update current data_set
	if (current_data_set_num == 2)
		current_data_set_num = 0;
	else if ((data_set_count==1)||(current_data_set_num==0))
		current_data_set_num = current_data_set_num;
	else
		current_data_set_num ++;

}

void display_dataset()
{
	// Last X, Y, Z readings and the state entry count
	LOG_INFO("Last: acc_x = %d, acc_y = %d, acc_z = %d",
			acc_x[current_data_set_num],
			acc_y[current_data_set_num],
			acc_z[current_data_set_num]);

	// Average X, Y, Z readings
	LOG_INFO("Average: acc_x = %d, acc_y = %d, acc_z = %d",
			average(acc_x,MAX_DATA_SET_COUNT),
			average(acc_y,MAX_DATA_SET_COUNT),
			average(acc_z,MAX_DATA_SET_COUNT));

	// Low X, Y, Z readings
	LOG_INFO("Low: acc_x = %d, acc_y = %d, acc_z = %d",
			min(acc_x,MAX_DATA_SET_COUNT),
			min(acc_y,MAX_DATA_SET_COUNT),
			min(acc_z,MAX_DATA_SET_COUNT));

	// High X, Y, Z readings
	LOG_INFO("High: acc_x = %d, acc_y = %d, acc_z = %d",
			max(acc_x,MAX_DATA_SET_COUNT),
			max(acc_y,MAX_DATA_SET_COUNT),
			max(acc_z,MAX_DATA_SET_COUNT));

}

