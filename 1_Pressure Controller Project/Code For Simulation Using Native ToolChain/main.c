/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */

#include "state.h"

#include "Pressure_Sensor_Driver.h"
#include "MainAlgorithm.h"
#include "AlarmMonitor.h"
#include "Alarm_Actuator_Driver.h"




void setup(void)
{
	//Initialization
	PressureSensor_init();
	AlarmActuatorDriver_init();

	PressureSensor_state = STATE(PressureSensor_Reading);
	MainAlgorithm_state = STATE(MainAlgorithm_HighPressureDetect);
	AlarmMonitor_state = STATE(AlarmMonitor_OFF);
	AlarmActuatorDriver_state = STATE(AlarmActuatorDriver_OFF);


}
int main ()
{
	setup();
	while(1)
	{
		PressureSensor_state();
		MainAlgorithm_state();
		AlarmMonitor_state();
//		AlarmActuatorDriver_state();
	}


	return 0;
}

