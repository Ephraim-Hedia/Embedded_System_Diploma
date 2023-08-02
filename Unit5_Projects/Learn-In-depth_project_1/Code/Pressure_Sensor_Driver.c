/*
 * Pressure_Sensor_Driver.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */


#include "state.h"
#include "Pressure_Sensor_Driver.h"

//Drivers For Hardware
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"


static int PressureSensorVal;



void (*PressureSensor_state )();


void PressureSensor_init()
{
	//Here We Will Initialize HW for Pressure Sensor
	//Pressure Sensor Connect with MicroController in PORTA PINs from 0 to 7
	MGPIO_voidSetByteDir(GPIOA,GPIO_BYTE_POSITION_LOW,GPIO_BYTE_INPUT_FLOATING);
}

//Declare States Functions PressureSensor
STATE_define(PressureSensor_Reading)
{
	//Set Enum Value for Debugging
	PressureSensor_state_id = PressureSensorReading;

	//Get Pressure Value
	PressureSensorVal = MGPIO_voidGetByteVal(GPIOA,GPIO_BYTE_POSITION_LOW);


	//Send Pressure Value to Main Algorithm Module
	PressureSensorDriver_setPressureVal(PressureSensorVal);

	//Set Next State
	PressureSensor_state = STATE(PressureSensor_Reading);

}


