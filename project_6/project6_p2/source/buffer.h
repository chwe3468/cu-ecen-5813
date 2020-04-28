/*
 * buffer.h
 *
 *  Created on: 4 20, 2020
 *      Author: Curry
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h> // size_t
#include <stdint.h> // uintx_t
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 64

typedef enum _errors{
	no_error = 0U,
	error_full = 1U,
	error_empty = 2U,
	error_buff_ptr = 3U,
	error_buf_init = 4U
}errors_t;

struct circular_buffer{
	char* buff_ptr;
	uint8_t head;
	uint8_t tail;
	uint8_t count;
};

errors_t initBuffer(struct circular_buffer *cbuff);
errors_t verifyInit(struct circular_buffer *cbuff);
errors_t verifyValidPointer(struct circular_buffer *cbuff);
errors_t destroyBuffer(struct circular_buffer *cbuff);
errors_t addItem(struct circular_buffer *cbuff, char item);
errors_t removeItem(struct circular_buffer *cbuff, char *item);
errors_t isFull(struct circular_buffer *cbuff);
errors_t isEmpty(struct circular_buffer *cbuff);

#endif
