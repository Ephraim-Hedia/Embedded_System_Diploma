/*
 * Pressure_Sensor_Driver.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */

#ifndef PRESSURE_SENSOR_DRIVER_H_
#define PRESSURE_SENSOR_DRIVER_H_


//Define States
enum {
	PressureSensorReading
}PressureSensor_state_id;

//STATE Pointer to Function
extern void (*PressureSensor_state )();


void PressureSensor_init();

//Declare States Functions CA
STATE_define(PressureSensor_Reading);




#endif /* PRESSURE_SENSOR_DRIVER_H_ */
