/*
 * Alarm_Actuator_Driver.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */


#include "state.h"
#include "Alarm_Actuator_Driver.h"


void (*AlarmActuatorDriver_state )();

void AlarmActuatorDriver_init(void)
{
	//Initialization
	printf("\n===================  AlarmActuatorDriver_init =================== \n");
}


void AlarmMonitor_StartAlarm()
{
	AlarmActuatorDriver_state =STATE(AlarmActuatorDriver_ON);
	AlarmActuatorDriver_state();
}
void AlarmMonitor_StopAlarm()
{
	AlarmActuatorDriver_state =STATE(AlarmActuatorDriver_OFF);
	AlarmActuatorDriver_state();
}

//Declare States Functions CA
STATE_define(AlarmActuatorDriver_ON)
{
	//Turn on Buzzer
	printf("\nAlarm ON");
	AlarmActuatorDriver_state =STATE(AlarmActuatorDriver_Waiting);

}
STATE_define(AlarmActuatorDriver_OFF)
{
	//Turn off Buzzer
	printf("\nAlarm OFF");
	printf("\n=========================================================\n");
	AlarmActuatorDriver_state =STATE(AlarmActuatorDriver_Waiting);

}
STATE_define(AlarmActuatorDriver_Waiting)
{
	printf("\nAlarm Waiting for any Request");
	printf("\n=========================================================\n");
}


