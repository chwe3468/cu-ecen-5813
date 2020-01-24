/**
 * @file  program_3.c
 * @brief program 3 for project 1
 *
 * This is the c program for program 3 specified in project 1
 * 
 *
 * @author Chutao Wei
 * @date Jan. 23 2020
 * @verison 1.0
 */	

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// the following binary pattern code is quoted from William Whyte
// and edited a little bit by me
// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format?page=1&tab=votes#tab-top

#define BYTE_TO_BINARY_PATTERN "0b%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

/**** ch function ****/
int check_0b1111(uint32_t num)
{
	if (num == 0b1111)
	{
		printf(" which is true\n");
	}
	else
	{
		printf(" which is false\n");
	}
}

/**** main function ****/
int main(void)
{
	// Step 1: Print the original input in hexadecimal
	uint16_t face = 0xFACE;
	uint16_t temp = 0;
	printf("Original value is: 0x%X\n", face);
	// Step 2: Test if 3 of last 4 bits are on
	temp = face&0xF;
	printf("binary value: "BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(temp));
	check_0b1111(temp);
	//Step 3: Reverse the byte order, print the value in hexadecimal
	face =	((face&0xF000)>>12)	+\
			((face&0x0F00)>>4 )	+\
			((face&0x00F0)<<4)	+\
			((face&0x000F)<<12);
    printf("Reverse byte value is: 0x%X\n", face);
	//Step 4: Test if 3 of last 4 bits are on
	temp = face&0xF;
	printf("binary value: "BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(temp));
	check_0b1111(temp);
	//Step 5: Rotate the value by six bits to the left
	face = (face<<6) | (face>>(32-6));
	printf("Rotate shift left 6 bits value is: 0x%X\n", face);
	//Step 6: Test if 3 of last 4 bits are on
	temp = face&0xF;
	printf("binary value: "BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(temp));
	check_0b1111(temp);
	//Step 7: Rotate the value by four bits to the right
    face = (face>>4) | (face<<(32-4));
    printf("Rotate shift right 4 bits value is: 0x%X\n", face);
	//Step 8: Test if 3 of last 4 bits are on
	temp = face&0xF;
	printf("binary value: "BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(temp));
	check_0b1111(temp);

	return 0;
}

