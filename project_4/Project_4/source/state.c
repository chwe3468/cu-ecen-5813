/*
 * state.c
 *
 *  Created on: Mar 31, 2020
 *      Author: user
 */

#include "state.h"

//from slides L16


void HandleAllEvents(tState *currentState){

}

void RunStateCentric(tMachine *currentMachine){
	tState *currentState= kReadXYZ;
	while (*currentMachine==0){
		//event=state=getEvent()
		switch(*currentState){
			case kReadXYZ:
				if (event==complete){

				}
				else if (event==disconnected){

				}
			case kProcessDisplay:
				if (event==complete){

				}
			case kSensorDisconnect:
				//exit()
			case kWaitPollSlider:
				if (event==timeout_1_5){

				}
				else if (event==timeout_6){

				}
				else if (event==leftSlider){

				}
				else if (event==rightSlider){

				}
		}
	}
}


//kReadXYZ, kProcessDisplay, kSensorDisconnect, kWaitPollSlider
void RunTableDriven(tMachine *currentMachine){
	sStateTableEntry *currentState= stateTable[kReadXYZ];
	while (*currentMachine==1){
		HandleEventComplete(struct sStateTableEntry *currentState){}
		HandleEventTimeout_1_5(struct sStateTableEntry *currentState){}
		HandleEventTimeout_6(struct sStateTableEntry *currentState){}
		HandleEventLeftSlider(struct sStateTableEntry *currentState){}
		HandleEventRightSlider(struct sStateTableEntry *currentState){}
		HandleEventDisconnected(struct sStateTableEntry *currentState){}
	}
}



void HandleEventComplete(struct sStateTableEntry *currentState){
	currentState=currentState->Complete;
}
void HandleEventTimeout_1_5(struct sStateTableEntry *currentState){
	currentState=currentState->Timout_1_5;
}
void HandleEventTimeout_6(struct sStateTableEntry *currentState){
	currentState=currentState->Timout_6;
}
void HandleEventLeftSlider(struct sStateTableEntry *currentState){
	currentState=currentState->LeftSlider;
}
void HandleEventRightSlider(struct sStateTableEntry *currentState){

	//currentState=currentState->RightSlider;
}
void HandleEventDisconnected(struct sStateTableEntry *currentState){

	//currentState=currentState->Disconnected;
}
