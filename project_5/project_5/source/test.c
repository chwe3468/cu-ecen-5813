/*
 * test.c
 *
 *  Created on: Apr 6, 2020
 *      Author: user
 */

#include "uCUnit.h"
#include "buffer.h"

//adapted from
//https://mcuoneclipse.com/2018/08/26/tutorial-%CE%BCcunit-a-unit-test-framework-for-microcontrollers/
void Test(void) {
	struct circular_buffer cbuff;
    char item;

    UCUNIT_Init(); /* initialize framework */
	UCUNIT_TestcaseBegin("Buffer Tests");

	UCUNIT_CheckIsEqual(0, initBuffer(&cbuff));
	UCUNIT_CheckIsEqual(0, destroyBuffer(&cbuff));

	initBuffer(&cbuff);
	cbuff.head=BUFFER_SIZE-1;
	cbuff.tail=BUFFER_SIZE-1;
	UCUNIT_CheckIsEqual(0, addItem(&cbuff,'a'));
	UCUNIT_CheckIsEqual(0, cbuff.head);
	UCUNIT_CheckIsEqual(0, addItem(&cbuff,'b'));
	UCUNIT_CheckIsEqual(0, addItem(&cbuff,'c'));
	UCUNIT_CheckIsEqual(0, removeItem(&cbuff, &item));
	printf("getitem: %s", item);
	UCUNIT_CheckIsEqual(0, cbuff.tail);
	UCUNIT_CheckIsEqual(0, removeItem(&cbuff, &item));
	printf("getitem: %s", item);
	UCUNIT_CheckIsEqual(0, removeItem(&cbuff, &item));
	printf("getitem: %s", item);
	destroyBuffer(&cbuff);

	initBuffer(&cbuff);
	for (int i=0; i<BUFFER_SIZE; i++){
		addItem(&cbuff,'a');
	}
	UCUNIT_CheckIsEqual(1U, addItem(&cbuff,'a'));

	for (int i=0; i<BUFFER_SIZE; i++){
		printf("%d, %s", removeItem(&cbuff, &item),item);
	}
	UCUNIT_CheckIsEqual(2U, removeItem(&cbuff, &item));
	destroyBuffer(&cbuff);


	UCUNIT_TestcaseEnd();

	/* finish all the tests */
	UCUNIT_WriteSummary();
	UCUNIT_Shutdown();
}
