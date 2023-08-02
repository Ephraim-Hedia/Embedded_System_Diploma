/*
 * AlarmMonitor.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */


#include "state.h"
#include "AlarmMonitor.h"

//Drivers For Hardware
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"

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


	AlarmMonitor_StartAlarm();

	//Turn on AlarmMonitor_Waiting State
	STATE(AlarmMonitor_Waiting)();

	//Set Next State
	AlarmMonitor_state = STATE(AlarmMonitor_OFF);

}

STATE_define(AlarmMonitor_OFF)
{
	//Set Enum Value for Debugging
	AlarmMonitor_state_id = AlarmMonitorOFF;

	//Stop Alarm
	AlarmMonitor_StopAlarm();

	//Set Next State
	AlarmMonitor_state = STATE(AlarmMonitor_OFF);
}

STATE_define(AlarmMonitor_Waiting)
{

	//Set Enum Value for Debugging
	AlarmMonitor_state_id = AlarmMonitorWaiting;

	//Set Timer
	MSTK_voidSetBusyWait(5000000);

	//Stop Alarm
	AlarmMonitor_StopAlarm();

	//Set Next State
	AlarmMonitor_state = STATE(AlarmMonitor_OFF);

}
