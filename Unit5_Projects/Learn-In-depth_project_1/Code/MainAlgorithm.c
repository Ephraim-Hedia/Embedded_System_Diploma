/*
 * MainAlgorithm.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */

#include "state.h"
#include "MainAlgorithm.h"

//Drivers For Hardware
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"


static int MainAlgorithmPressureVal;
static int MainAlgorithmThreshold = 20;


void (*MainAlgorithm_state )();

void PressureSensorDriver_setPressureVal(int pVal)
{
	MainAlgorithmPressureVal = pVal;
}


STATE_define(MainAlgorithm_HighPressureDetect)
{

	//Set Enum Value for Debugging
	MainAlgorithm_state_id = MainAlgorithmHighPressureDetect;

	if (MainAlgorithmPressureVal > MainAlgorithmThreshold)
	{
		MainAlgorithm_HighPressureDetected(PressureDetected);
	}
	else
	{
		MainAlgorithm_HighPressureDetected(PressureNotDetected);
	}
	//Set Next State
	MainAlgorithm_state = STATE(MainAlgorithm_HighPressureDetect);

}
