/*
 * CA.h
 *
 *  Created on: Sep 12, 2022
 *      Author: Guirguis
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"
//Define States
enum {
	CA_waiting,
	CA_driving
}CA_state_id;

//STATE Pointer to Function
extern void (*CA_state )();

//Declare States Functions CA
STATE_define(CA_waiting);
STATE_define(CA_driving);
#endif /* CA_H_ */
