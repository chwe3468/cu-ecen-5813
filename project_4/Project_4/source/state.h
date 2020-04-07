/*
 * state.h
 *
 *  Created on: Mar 31, 2020
 *      Author: user
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdlib.h>
//adapted from
//https://stackoverflow.com/questions/133214/is-there-a-typical-state-machine-implementation-pattern/44955234
//https://kjarvel.wordpress.com/2011/10/26/table-driven-state-machine-using-function-pointers-in-c/
/********************** Enumeration ***********************/



/********************** Enumeration ***********************/

typedef enum{ mStateCentric, mTableDriven} tMachine;
typedef enum{ kReadXYZ, kProcessDisplay, kWaitPollSlider, NUM_STATES} tState;
typedef enum{ Complete, Timeout_1_5, Timeout_6, LeftSlider, RightSlider, Start} tEvent;

/********************** Structure ***********************/

//#define

typedef void state_func();

void state_ReadXYZ();
void state_Display();
void state_WaitPoll();
void SetEvent(tEvent evt);

struct sStateTableEntry{
	//tState current_state;       	// all states have associated lights
	tEvent Complete;
	tEvent Timeout_1_5;
	tEvent Timeout_6;
	tEvent LeftSlider;
	tEvent RightSlider;
	state_func *func_p;
};

struct sStateTableEntry stateTable[] = {
		//complete, timeout_1_5, timout_6, left_slider, right_slider, state_func
		{kProcessDisplay, kReadXYZ, kReadXYZ, kReadXYZ, kReadXYZ, state_ReadXYZ}, //readXYZ
		{kWaitPollSlider, kProcessDisplay, kProcessDisplay, kProcessDisplay, kProcessDisplay, state_Display}, //processDisplay
		{kWaitPollSlider, kReadXYZ, kReadXYZ, kReadXYZ, kReadXYZ, state_WaitPoll} //WaitPollSLider
};


/********************** Prototype ***********************/

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

