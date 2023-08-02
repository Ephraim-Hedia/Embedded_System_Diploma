/*
 * Alarm_Actuator_Driver.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */

#ifndef ALARM_ACTUATOR_DRIVER_H_
#define ALARM_ACTUATOR_DRIVER_H_



//Define States
enum {
	AlarmActuatorDriverON,
	AlarmActuatorDriverOFF,
	AlarmActuatorDriverWaiting
}AlarmActuatorDriver_state_id;

void AlarmActuatorDriver_init(void);

//STATE Pointer to Function
extern void (*AlarmActuatorDriver_state )();


//Declare States Functions CA
STATE_define(AlarmActuatorDriver_ON);
STATE_define(AlarmActuatorDriver_OFF);
STATE_define(AlarmActuatorDriver_Waiting);


#endif /* ALARM_ACTUATOR_DRIVER_H_ */
