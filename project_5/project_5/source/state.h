/*
 * state.h
 *
 *  Created on: Mar 31, 2020
 *      Author: user
 */

#ifndef STATE_H_
#define STATE_H_

//adapted from
//https://stackoverflow.com/questions/133214/is-there-a-typical-state-machine-implementation-pattern/44955234
//https://kjarvel.wordpress.com/2011/10/26/table-driven-state-machine-using-function-pointers-in-c/

/********************** Include ***********************/

#include <stdlib.h>

/********************** Enumeration ***********************/

typedef enum{
	mStateCentric = 0,
	mTableDriven = 1
} tMachine;
typedef enum{
	kReadXYZ = 0,
	kProcessDisplay = 1,
	kWaitPollSlider = 2,
	kEnd = 3,
	kError = 4
} tState;
typedef enum{
	Complete = 0,
	Timeout_1_5 = 1,
	Timeout_6 = 2,
	LeftSlider = 3,
	RightSlider = 4
} tEvent;

/********************** Structure ***********************/

typedef void state_func();

struct sStateTableEntry{
	state_func *func_p; // action correspond to the state
	tState next_state[6];
};


/********************** Prototype ***********************/

/* State Machine function */
void state_ReadXYZ();
void state_Display();
void state_WaitPoll();
void state_End();
void state_Error();
void SetEvent(tEvent evt);

/* Two different State Machine */
void RunMachines(void);
void RunStateCentric(void);
void RunTableDriven(void);

/* Event Handlers */
//void HandleAllEvents(tState *currentState);
void HandleEventComplete(void);
void HandleEventTimeout_1_5(void);
void HandleEventTimeout_6(void);
void HandleEventLeftSlider(void);
void HandleEventRightSlider(void);
void HandleEventDisconnected(void);


#endif /* STATE_H_ */

