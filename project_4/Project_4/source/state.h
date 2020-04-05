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

/********************** Enumeration ***********************/

#include <stdlib.h>

/********************** Enumeration ***********************/

typedef enum{ mStateCentric, mTableDriven} tMachine;
typedef enum{ kReadXYZ, kProcessDisplay, kSensorDisconnect, kWaitPollSlider, NUM_STATES} tState;
typedef enum{ complete, timeout_1_5, timeout_6, leftSlider, rightSlider, disconnected} tEvent;
typedef struct instance_data instance_data_t;

/********************** Structure ***********************/

typedef state_t state_func_t(instance_data_t *data);


struct sStateTableEntry stateTable[] = {
		//complete, timeout_1_5, timout_6, left_slider, right_slider, disconnected
		{kProcessDisplay, kReadXYZ, kReadXYZ, kReadXYZ, kReadXYZ, kSensorDisconnect}, //readXYZ
		{kWaitPollSlider, kProcessDisplay, kProcessDisplay, kProcessDisplay, kProcessDisplay, kProcessDisplay}, //processDisplay
		{NULL, NULL, NULL, NULL, NULL, NULL}, //SensorDisconnect
		{kWaitPollSlider, kReadXYZ, kReadXYZ, kReadXYZ, NULL, kWaitPollSlider} //WaitPollSLider
};

struct sStateTableEntry{
	//tState current_state;       	// all states have associated lights
	tEvent complete;
	tEvent timeout_1_5;
	tEvent timeout_6;
	tEvent leftSlider;
	tEvent rightSlider;
	tEvent disconnected;
};


/********************** Prototype ***********************/

/* Two different State Machine */
void RunStateCentric(tMachine *currentMachine);
void RunTableDriven(tMachine *currentMachine);

/* Event Handlers */
void HandleAllEvents(tState *currentState);

void HandleEventComplete(struct sStateTableEntry *currentState);
void HandleEventTimeout_1_5(struct sStateTableEntry *currentState);
void HandleEventTimeout_6(struct sStateTableEntry *currentState);
void HandleEventLeftSlider(struct sStateTableEntry *currentState);
void HandleEventRightSlider(struct sStateTableEntry *currentState);
void HandleEventDisconnected(struct sStateTableEntry *currentState);


#endif /* STATE_H_ */
