/*
 * AlarmMonitor.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */

#ifndef ALARMMONITOR_H_
#define ALARMMONITOR_H_


//Define States
enum {
	AlarmMonitorON,
	AlarmMonitorOFF,
	AlarmMonitorWaiting
}AlarmMonitor_state_id;

//STATE Pointer to Function
extern void (*AlarmMonitor_state )();


//Declare States Functions CA
STATE_define(AlarmMonitor_ON);
STATE_define(AlarmMonitor_OFF);
STATE_define(AlarmMonitor_Waiting);

#endif /* ALARMMONITOR_H_ */
