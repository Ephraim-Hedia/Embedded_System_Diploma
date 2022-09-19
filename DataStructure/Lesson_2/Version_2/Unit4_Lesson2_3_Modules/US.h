/*
 * US.h
 *
 *  Created on: Sep 12, 2022
 *      Author: Guirguis
 */

#ifndef US_H_
#define US_H_

#include "state.h"
//Define States
enum {
	US_busy,
}US_state_id;

//STATE Pointer to Function
extern void (*US_state )();

void US_init();

//Declare States Functions US
STATE_define(US_busy);
#endif /* US_H_ */
