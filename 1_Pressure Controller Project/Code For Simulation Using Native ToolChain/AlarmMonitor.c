/*
 * AlarmMonitor.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */


#include "state.h"
#include "AlarmMonitor.h"


void (*AlarmMonitor_state )();

void MainAlgorithm_HighPressureDetected(PressureState Pstate)
{
	switch(Pstate)
	{
	case PressureDetected:
		AlarmMonitor_state = STATE(AlarmMonitor_ON);
		break;
	case PressureNotDetected:
		AlarmMonitor_state = STATE(AlarmMonitor_OFF);
		break;
	default:
		break;
	}

}

STATE_define(AlarmMonitor_ON)
{
	//Set Enum Value for Debugging
	AlarmMonitor_state_id = AlarmMonitorON;

	printf("\nAlarmMonitor_StartAlarm");
	//Start Alarm
	AlarmMonitor_StartAlarm();

	//Set Timer
	printf("\nSet Timer");

	//Turn on AlarmMonitor_Waiting State
	printf("\nTurn on Waiting State");
	STATE(AlarmMonitor_Waiting)();

	//Set Next State
	AlarmMonitor_state = STATE(AlarmMonitor_OFF);

}

STATE_define(AlarmMonitor_OFF)
{

	//Set Enum Value for Debugging
	AlarmMonitor_state_id = AlarmMonitorOFF;

	printf("\nAlarmMonitor_StopAlarm");
	//Stop Alarm
	AlarmMonitor_StopAlarm();

	//Set Next State
	AlarmMonitor_state = STATE(AlarmMonitor_OFF);
}

STATE_define(AlarmMonitor_Waiting)
{
	//Set Enum Value for Debugging
	AlarmMonitor_state_id = AlarmMonitorWaiting;

	//Check if the Time Expired
	printf("\nWaiting Till Timer Expired");

	//Reset Timer
	printf("\nReset Timer ");

	//Stop Alarm
	printf("\nStop Alarm ");
	AlarmMonitor_StopAlarm();

	//Set Next State
	AlarmMonitor_state = STATE(AlarmMonitor_OFF);

}
