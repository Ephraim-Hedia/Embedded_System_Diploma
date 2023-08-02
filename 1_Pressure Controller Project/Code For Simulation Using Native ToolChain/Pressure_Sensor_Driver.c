/*
 * Pressure_Sensor_Driver.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */


#include "state.h"
#include "Pressure_Sensor_Driver.h"

static int PressureSensorVal;

static int PressureSensor_GetRandomPressure(int l,int r);

void (*PressureSensor_state )();


void PressureSensor_init()
{
	printf("\n===================  PressureSensor_init ===================");
}

//Declare States Functions CA
STATE_define(PressureSensor_Reading)
{
	//Set Enum Value for Debugging
	PressureSensor_state_id = PressureSensorReading;

	//Get Pressure Value
	PressureSensorVal = PressureSensor_GetRandomPressure(15,25);
	printf("\nPressure Sensor Val --> %d",PressureSensorVal);

	//Send Pressure Value to Main Algorithm Module
	PressureSensorDriver_setPressureVal(PressureSensorVal);

	//Set Next State
	PressureSensor_state = STATE(PressureSensor_Reading);

}


int PressureSensor_GetRandomPressure(int l,int r)
{

	int rand_num = (rand() % (r - l + 1)) + l;
	return rand_num;

}
