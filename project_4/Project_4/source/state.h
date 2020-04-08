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

typedef enum{ mStateCentric, mTableDriven} tMachine;
typedef enum{ kReadXYZ, kProcessDisplay, kWaitPollSlider} tState;
typedef enum{ Complete, Timeout_1_5, Timeout_6, LeftSlider, RightSlider, Start} tEvent;

/********************** Structure ***********************/

typedef void state_func();

struct sStateTableEntry{
	//tState current_state;       	// all states have associated lights
	tEvent Complete;
	tEvent Timeout_1_5;
	tEvent Timeout_6;
	tEvent LeftSlider;
	tEvent RightSlider;
	state_func *func_p;
};


/********************** Prototype ***********************/

/* State Machine function */
void state_ReadXYZ();
void state_Display();
void state_WaitPoll();
void SetEvent(tEvent evt);

/* Two different State Machine */
void RunMachines();
void RunStateCentric();
void RunTableDriven();

/* Event Handlers */
//void HandleAllEvents(tState *currentState);
void HandleEventComplete();
void HandleEventTimeout_1_5();
void HandleEventTimeout_6();
void HandleEventLeftSlider();
void HandleEventRightSlider();
void HandleEventDisconnected();


#endif /* STATE_H_ */

