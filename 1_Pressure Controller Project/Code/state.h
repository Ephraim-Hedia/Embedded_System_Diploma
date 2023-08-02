/*
 * state.h
 *
 *  Created on: Sep 12, 2022
 *      Author: ff
 */

#ifndef STATE_H_
#define STATE_H_
#include "stdio.h"
#include "stdlib.h"

typedef enum
{
	PressureDetected,
	PressureNotDetected
}PressureState;


//Automatic State Function Generated
#define STATE_define(_statFUN_)	void ST_##_statFUN_()
#define STATE(_statFUN_)	 ST_##_statFUN_


//States Connection
extern void PressureSensorDriver_setPressureVal(int pVal);
extern void MainAlgorithm_HighPressureDetected(PressureState Pstate);
extern void AlarmMonitor_StartAlarm();
extern void AlarmMonitor_StopAlarm();



#endif /* STATE_H_ */
