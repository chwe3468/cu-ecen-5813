/*
 * state.c
 *
 *  Created on: Mar 31, 2020
 *      Author: user
 */

#include "state.h"

//from slides L16

tEvent event=Start;
tMachine machine=mStateCentric;
static int x,y,z;

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
//	sStateTableEntry *currentState= stateTable[kReadXYZ];
	tState currentState= kReadXYZ;
	while (machine=mStateCentric){
		//event=state=getEvent()
		tableDriven[currentState].func_p();
		switch(currentState){
		case kReadXYZ:
			/* Handel Event */
			/* Prepare for new state */
			/* Set new state*/
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
}


//kReadXYZ, kProcessDisplay, kSensorDisconnect, kWaitPollSlider
void RunTableDriven(tMachine *currentMachine){
	//sStateTableEntry *currentState= stateTable[kReadXYZ];
	tState currentState= kReadXYZ;
	while (machine==mTableDriven){
		tableDriven[currentState].func_p();
		HandleEventComplete();
		HandleEventTimeout_1_5();
		HandleEventTimeout_6();
		HandleEventLeftSlider();
		HandleEventRightSlider();
	}
}

void HandleEventComplete(void){
	currentState=stateTable[currentState].Complete;
}
void HandleEventTimeout_1_5(void){
	currentState=stateTable[currentState].Timout_1_5;
}
void HandleEventTimeout_6(void){
	currentState=stateTable[currentState].Timout_6;
}
void HandleEventLeftSlider(void){
	machine!=machine;
	currentState=stateTable[currentState].LeftSlider;
}
void HandleEventRightSlider(void){
	exit(0);
	//currentState=currentState->RightSlider;
}
