/*
 * state.c
 *
 *  Created on: Mar 31, 2020
 *      Author: user
 */

/********************** Include ***********************/

#include <stdio.h>
#include "state.h"
#include "timer.h"
#include "mma8451.h"
#include "touch_sen.h"
#include "logger.h"


/********************** Global Variables ***********************/

/* State machine relted varibles */
tEvent event=Start;
tMachine machine=mStateCentric;
tState currentState= kReadXYZ;

/* State Table used by RunTableDriven() function */
struct sStateTableEntry stateTable[] = {
		//complete, timeout_1_5, timout_6, left_slider, right_slider, state_func
		{kProcessDisplay, kReadXYZ, kReadXYZ, kReadXYZ, kReadXYZ, state_ReadXYZ}, //readXYZ
		{kWaitPollSlider, kProcessDisplay, kProcessDisplay, kProcessDisplay, kProcessDisplay, state_Display}, //processDisplay
		{kWaitPollSlider, kReadXYZ, kReadXYZ, kReadXYZ, kReadXYZ, state_WaitPoll} //WaitPollSLider
};

//static int x,y,z;

/********************** Function ***********************/

/* State Machine function */
void state_ReadXYZ(){
	//readxyz
}

void state_Display(){
	//display
}

void state_WaitPoll(){
	//waitpoll systick/poll
}

void SetEvent(tEvent evt){
	event = evt;
}

void RunMachines(){
	switch(machine){
		case mStateCentric:
			RunStateCentric();
		case mTableDriven:
			RunTableDriven();
	}
}

void RunStateCentric(){
	//sStateTableEntry *currentState= stateTable[kReadXYZ];
	/* Do the action in this state */
	stateTable[currentState].func_p();

	/* Set the state to go next */
	switch(currentState){
	case kReadXYZ:

		if (event==Complete){
			HandleEventComplete();
		}
		else{
			printf("%d",(int)event);
		}
	case kProcessDisplay:
		if (event==Complete){
			HandleEventComplete();
		}
		else{
			printf("%d",(int)event);
		}
	case kWaitPollSlider:
		if (event==Timeout_1_5){
			HandleEventTimeout_1_5();
		}
		else if (event==Timeout_6){
			HandleEventTimeout_6();
		}
		else if (event==LeftSlider){
			HandleEventLeftSlider();
		}
		else if (event==RightSlider){
			HandleEventRightSlider();
		}
		else{
			printf("%d",(int)event);
		}
	}
}


//kReadXYZ, kProcessDisplay, kSensorDisconnect, kWaitPollSlider
void RunTableDriven(tMachine *currentMachine){
	//sStateTableEntry *currentState= stateTable[kReadXYZ];
	/* Do the action in this state */
	stateTable[currentState].func_p();

	/* Set the state to go next */
	HandleEventComplete();
	HandleEventTimeout_1_5();
	HandleEventTimeout_6();
	HandleEventLeftSlider();
	HandleEventRightSlider();
}

void HandleEventComplete(void){
	currentState=stateTable[currentState].Complete;
}
void HandleEventTimeout_1_5(void){
	currentState=stateTable[currentState].Timeout_1_5;
}
void HandleEventTimeout_6(void){
	currentState=stateTable[currentState].Timeout_6;
}
void HandleEventLeftSlider(void){
	machine=!machine;
	currentState=stateTable[currentState].LeftSlider;
}
void HandleEventRightSlider(void){
	exit(0);
	//currentState=currentState->RightSlider;
}

