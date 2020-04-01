/*
 * state.h
 *
 *  Created on: Mar 31, 2020
 *      Author: user
 */

#ifndef STATE_H_
#define STATE_H_



#endif /* STATE_H_ */

//adapted from
//https://stackoverflow.com/questions/133214/is-there-a-typical-state-machine-implementation-pattern/44955234
typedef enum{ mStateCentric, mTableDriven} tMachine;
typedef enum{ kReadXYZ, kProcessDisplay, kSensorDisconnect, kWaitPollSlider, NUM_STATES} tState;
typedef enum{ complete, timeout_1_5, timout_6, leftSlider, rightSlider, disconnected} tEvents;
typedef struct instance_data instance_data_t;
typedef state_t state_func_t( instance_data_t *data);

struct sStateTableEntry stateTable[] = {
		//complete, timeout_1_5, timout_6, left_slider, right_slider, disconnected
		{kProcessDisplay, kReadXYZ, kReadXYZ, kReadXYZ, kReadXYZ, kSensorDisconnect}, //readXYZ
		{kWaitPollSlider, kProcessDisplay, kProcessDisplay, kProcessDisplay, kProcessDisplay, kProcessDisplay}, //processDisplay
		{NULL, NULL, NULL, NULL, NULL, NULL}, //SensorDisconnect
		{kWaitPollSlider, kReadXYZ, kReadXYZ, kReadXYZ, NULL, kWaitPollSlider} //WaitPollSLider
	}

struct sStateTableEntry{
	//tState current_state;       	// all states have associated lights
	tState Complete;
	tState Timeout_1_5;
	tState Timeout_6;
	tState LeftSlider;
	tState RightSlider;
	tState Disconnected;
};

void RunStateCentric(tState *currentState, tMachine *currentMachine){}
void RunTableDriven(tState *currentState, tMachine *currentMachine){}

void HandleAllEvents(tState *currentState){}

void HandleEventComplete(struct sStateTableEntry *currentState){}
void HandleEventTimeout_1_5(struct sStateTableEntry *currentState){}
void HandleEventTimeout_6(struct sStateTableEntry *currentState){}
void HandleEventLeftSlider(struct sStateTableEntry *currentState){}
void HandleEventRightSlider(struct sStateTableEntry *currentState){}
void HandleEventDisconnected(struct sStateTableEntry *currentState){}
