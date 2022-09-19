/*
 * CA.h
 *
 *  Created on: Sep 12, 2022
 *      Author: Guirguis
 */

#ifndef DC_H_
#define DC_H_

#include "state.h"
//Define States
enum {
	DC_idle,
	DC_busy
}DC_state_id;

//STATE Pointer to Function
extern void (*DC_state )();



void DC_init();
//Declare States Functions CA
STATE_define(DC_idle);
STATE_define(DC_busy);
#endif /* DC_H_ */
