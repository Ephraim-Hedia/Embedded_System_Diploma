/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */


//Drivers For Hardware
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"

//APP Modules
#include "state.h"
#include "Pressure_Sensor_Driver.h"
#include "MainAlgorithm.h"
#include "AlarmMonitor.h"
#include "Alarm_Actuator_Driver.h"

void HW_voidInit(void)
{
	//Initialize Systick Timer
	MSTK_voidInit();
	//Initialize Reset and Clock COntroller
	RCC_voidInitSystemClk();
	//Enable Clock for PORTA
	RCC_u8EnableClock(RCC_APB2,RCC_APB2_IOPA);
}


void setup(void)
{
	//Initialization

	HW_voidInit();
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

	}


	return 0;
}

