/*
 * MainAlgorithm.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Ephraim
 */

#ifndef MAINALGORITHM_H_
#define MAINALGORITHM_H_



//Define States
enum {
	MainAlgorithmHighPressureDetect
}MainAlgorithm_state_id;

//STATE Pointer to Function
extern void (*MainAlgorithm_state )();

//Declare States Functions CA
STATE_define(MainAlgorithm_HighPressureDetect);

#endif /* MAINALGORITHM_H_ */
