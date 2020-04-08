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
#include "led.h"

/********************** Global Variables ***********************/

/* State machine relted varibles */
tEvent event = RightSlider;
tMachine machine=mStateCentric;
tState currentState= kReadXYZ;

/* State Table used by RunTableDriven() function */
struct sStateTableEntry stateTable[] = {
/* CurrentState 	    Action function  Event:complete   timeout_1_5, timout_6, left_slider, right_slider */
/* kReadXYZ */			{state_ReadXYZ, {kProcessDisplay, kError,      kError,   kError,      kError      }},
/* kProcessDisplay */	{state_Display, {kWaitPollSlider, kError,      kError,   kError,      kError      }},
/* kWaitPollSlider */	{state_WaitPoll,{kError,          kReadXYZ,    kReadXYZ, kReadXYZ,    kEnd        }},
/* kend */				{state_End,		{kEnd,            kEnd,        kEnd,     kEnd,        kEnd        }},
/* kerror */			{state_Error,	{kError,          kError,      kError,   kError,      kError      }}
};

const char * state_machine_type_string[2] ={"StateCentric","TableDriven"};
/********************** Function ***********************/

/* State Machine action functions */
void state_ReadXYZ(){
	read_full_xyz();
	SetEvent(Complete);
}

void state_Display(){
	display_dataset();
	SetEvent(Complete);
}

void state_WaitPoll(){
	mdelay(3000);

	tsi_position_t final_pos;
	// wait until SysTick_Handler set timeout event flag
	uint32_t left_pos_count = 0;
	uint32_t right_pos_count = 0;
	while(event == Complete)
	{
		// keep polling slider position
		tsi_position_t pos = Touch_Scan_Position();
		if (pos == left)
			left_pos_count++;
		else if (pos == right)
			right_pos_count++;
	}

	if (left_pos_count > right_pos_count)
		final_pos = left;
	else if (left_pos_count < right_pos_count)
		final_pos = right;
	else
		final_pos = left;
	// if slider is right or event is timeout_6
	if ((final_pos == right) || (event == Timeout_6))
	{
		// change to the other state machine
		machine = machine ^ 0x1;
	}
}

void state_End(){
	// halt the program
	turn_LED_green(off);
	turn_LED_red(on);
	while(1);
}

void state_Error(){
	// halt the program
	while(1);
}

void SetEvent(tEvent evt){
	event = evt;
}

/* state machine related functions */
void RunMachines(void){
	LOG_INFO("current state machine is %s",state_machine_type_string[machine]);
	switch(machine){
		case mStateCentric:
			RunStateCentric();
			break;
		case mTableDriven:
			RunTableDriven();
			break;
	}
}

void RunStateCentric(void){
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
			printf("last event is %d",(int)event);
		}
		break;
	case kProcessDisplay:
		if (event==Complete){
			HandleEventComplete();
		}
		else{
			printf("last event is %d",(int)event);
		}
		break;
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
			LOG_ERROR("last event is %d",(int)event);
		}
		break;
	default:
		LOG_ERROR("Error state reached");
		LOG_ERROR("last event is %d",(int)event);
		break;
	}
}


//kReadXYZ, kProcessDisplay, kSensorDisconnect, kWaitPollSlider
void RunTableDriven(void){
	//sStateTableEntry *currentState= stateTable[kReadXYZ];
	/* Do the action in this state */
	stateTable[currentState].func_p();

	/* Set the state to go next */
	currentState=stateTable[currentState].next_state[event];
}

void HandleEventComplete(void){
	currentState=stateTable[currentState].next_state[Complete];
}
void HandleEventTimeout_1_5(void){
	currentState=stateTable[currentState].next_state[Timeout_1_5];
}
void HandleEventTimeout_6(void){
	currentState=stateTable[currentState].next_state[Timeout_6];
}
void HandleEventLeftSlider(void){
	currentState=stateTable[currentState].next_state[LeftSlider];
}
void HandleEventRightSlider(void){
	currentState=stateTable[currentState].next_state[RightSlider];
}

