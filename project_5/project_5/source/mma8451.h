/*
 * mma8451.h
 *
 *  Created on: Apr 1, 2020
 *      Author: user
 */
//adapted from https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/

#ifndef MMA8451_H
#define MMA8451_H

/*************** Include *****************/

#include <stdint.h>

/*************** Define *****************/
// I2C address
#define MMA_ADDR 0x1D

// Register address mapping
#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D

#define WHOAMI 0x1A

// Math constant
#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)

/*************** Prototype *****************/

/*************************************************
 * @brief
 *   Initializes mma8451 sensor
 * @note
 *   i2c has to already be enabled
 ************************************************/
int init_mma8451(void);

/*************************************************
 * @brief
 *   Make sure mma8451 is connection by reading
 *   who_am_i register on mma8451
 ************************************************/
int verify_connect_mma8451(void);

/*************************************************
 * @brief
 *   read MMA8451 acc_x,y and z data in 16 bits
 *   format
 * @note
 *   i2c has to already be enabled
 ************************************************/
void read_full_xyz(void);

/*************************************************
 * @brief
 *   read MMA8451 acc_x,y and z data in 8 bits
 *   format but sign extend to 16 bits.
 * @note
 *   i2c has to already be enabled
 ************************************************/
void read_xyz(void);

/*************************************************
 * @brief
 *   print xyz dataset using LOG_INFO
 *   as required by PES project_4
 ************************************************/
void display_dataset(void);

#endif
