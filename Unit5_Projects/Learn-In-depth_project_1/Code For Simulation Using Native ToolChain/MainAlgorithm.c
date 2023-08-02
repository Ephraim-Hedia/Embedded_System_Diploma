/*
 * MainAlgorithm.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */

#include "state.h"
#include "MainAlgorithm.h"

static int MainAlgorithmPressureVal;
static int MainAlgorithmThreshold = 20;


void (*MainAlgorithm_state )();

void PressureSensorDriver_setPressureVal(int pVal)
{
	MainAlgorithmPressureVal = pVal;
	printf("\nSet Main Algorithm Pressure Value =%d ",MainAlgorithmPressureVal);

}


STATE_define(MainAlgorithm_HighPressureDetect)
{

	//Set Enum Value for Debugging
	MainAlgorithm_state_id = MainAlgorithmHighPressureDetect;

	if (MainAlgorithmPressureVal > MainAlgorithmThreshold)
	{
		printf("\n%d > Main Algorithm Threshold" ,MainAlgorithmPressureVal);
		MainAlgorithm_HighPressureDetected(PressureDetected);
	}
	else
	{
		printf("\n%d < Main Algorithm Threshold" ,MainAlgorithmPressureVal);
		MainAlgorithm_HighPressureDetected(PressureNotDetected);
	}


	//Set Next State
	MainAlgorithm_state = STATE(MainAlgorithm_HighPressureDetect);

}
