/*
 * test.c
 *
 *  Created on: Apr 6, 2020
 *      Author: user
 */

#include "uCUnit.h"
#include "state.h"

//adapted from
//https://mcuoneclipse.com/2018/08/26/tutorial-%CE%BCcunit-a-unit-test-framework-for-microcontrollers/
void Test(void) {
	tEvent test_event=kReadXYZ;
	tMachine test_machine=mStateCentric;

	UCUNIT_Init(); /* initialize framework */
	UCUNIT_TestcaseBegin("State_Machine_Transitions");
	HandleEventComplete();
	UCUNIT_CheckIsEqual(test_event, kProcessDisplay);
	HandleEventComplete();
	UCUNIT_CheckIsEqual(test_event, kWaitPollSlider);
	HandleEventTimeout_1_5();
	UCUNIT_CheckIsEqual(test_event, kReadXYZ);

	test_event=kWaitPollSlider;
	HandleEventTimeout_6();
	UCUNIT_CheckIsEqual(test_event, kReadXYZ);
	UCUNIT_CheckIsEqual(test_machine, mTableDriven);
	test_event=kWaitPollSlider;
	HandleEventLeftSlider();
	UCUNIT_CheckIsEqual(test_event, kReadXYZ);
	UCUNIT_CheckIsEqual(test_machine, mStateCentric);

	UCUNIT_TestcaseEnd();

	/* finish all the tests */
	UCUNIT_WriteSummary();
	UCUNIT_Shutdown();
}
