#include "buffer.h"

errors_t error;

errors_t initBuffer(struct circular_buffer *cbuff){
	error=no_error;
	cbuff->buff_ptr= malloc(BUFFER_SIZE * sizeof(char));
	if (!verifyValidPointer(cbuff)){
		for (int i=0; i<BUFFER_SIZE; i++){
			cbuff->buff_ptr[i]='0';
		}
		if (!verifyInit(cbuff)){
			cbuff->head=0;
			cbuff->tail=0;
			cbuff->count=0;
		}
	}
	return error;
}
errors_t verifyInit(struct circular_buffer *cbuff){
	error=no_error;
	for (int i=0; i<BUFFER_SIZE; i++){
		if (cbuff->buff_ptr[i]!='0'){
			error=error_buf_init;
		}
	}
	return error;
}
errors_t verifyValidPointer(struct circular_buffer *cbuff){
	error=no_error;
	if (cbuff->buff_ptr==NULL){
		error=error_buff_ptr;
	}
	return error;
}
errors_t destroyBuffer(struct circular_buffer *cbuff){
	error=no_error;
	free(cbuff->buff_ptr);
	return error;
}
errors_t addItem(struct circular_buffer *cbuff, char item){
	error=no_error;
	if (!isFull(cbuff)){
		cbuff->buff_ptr[cbuff->head]=item;
		cbuff->head=(cbuff->head+1)%BUFFER_SIZE;
		cbuff->count++;
	}
	return error;
}
errors_t removeItem(struct circular_buffer *cbuff, char *item){
	error=no_error;
	if (!isEmpty(cbuff)){
		*item=cbuff->buff_ptr[cbuff->tail];
		cbuff->tail=(cbuff->tail+1)%BUFFER_SIZE;
		cbuff->count--;
	}
	return error;
}
errors_t isFull(struct circular_buffer *cbuff){
	error=no_error;
	if (cbuff->count==BUFFER_SIZE){
		error=error_full;
	}
	return error;
}
errors_t isEmpty(struct circular_buffer *cbuff){
	error=no_error;
	if (cbuff->count==0){
		error=error_empty;
	}
	return error;
}
