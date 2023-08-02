/*
 * Alarm_Actuator_Driver.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */


#include "state.h"
#include "Alarm_Actuator_Driver.h"


//Drivers For Hardware
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"




void (*AlarmActuatorDriver_state )();

void AlarmActuatorDriver_init(void)
{
	//Initialization for HW of Buzzer which is Connected with MicroController with pin 13
	MGPIO_voidSetPinDir(GPIOA,GPIO_PIN13,GPIO_OUTPUT_SPEED_2MHz_PP);
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
	MGPIO_voidSetPinVal(GPIOA,GPIO_PIN13,GPIO_LOW);
	AlarmActuatorDriver_state =STATE(AlarmActuatorDriver_Waiting);

}
STATE_define(AlarmActuatorDriver_OFF)
{
	//Turn off Buzzer
	MGPIO_voidSetPinVal(GPIOA,GPIO_PIN13,GPIO_HIGH);
	AlarmActuatorDriver_state =STATE(AlarmActuatorDriver_Waiting);

}
STATE_define(AlarmActuatorDriver_Waiting)
{
	//NO Thing
	//Just Waiting for any change
}


