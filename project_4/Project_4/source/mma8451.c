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
#include <math.h>


/*************** Global *****************/
// data variables
int16_t acc_x=0, acc_y=0, acc_z=0;
float roll=0.0, pitch=0.0;

//mma data ready
extern uint32_t DATA_READY;

/*************** Function *****************/

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
	acc_x = temp[0]>>2;
	acc_y = temp[1]>>2;
	acc_z = temp[2]>>2;
}


void read_xyz(void)
{
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	acc_x = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI);
	mdelay(100);
	acc_y = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI);
	mdelay(100);
	acc_z = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI);

}

void convert_xyz_to_roll_pitch(void) {
	float ax = acc_x/COUNTS_PER_G,
				ay = acc_y/COUNTS_PER_G,
				az = acc_z/COUNTS_PER_G;

	roll = atan2(ay, az)*180/M_PI;
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;

}


//mma data ready irq
// void PORTA_IRQHandler()
// {
// 	NVIC_ClearPendingIRQ(PORTA_IRQn);
// 	DATA_READY = 1;
// }
