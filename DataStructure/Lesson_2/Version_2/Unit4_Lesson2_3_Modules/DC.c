/*
 * DC.c
 *
 *  Created on: Sep 12, 2022
 *      Author: ff
 */

#include "DC.h"
//Variables
int DC_speed;

//STATE Pointer to Function
void (*DC_state )();


void DC_init()
{
	//init PWM
	printf("DC_init \n");

}

void DC_motor (int s)
{
	DC_speed=s;
	(DC_speed ==0)?(DC_state=STATE(DC_idle)):(DC_state=STATE(DC_busy));
	printf("CA-------speed=%d--------->DC\n",DC_speed);
}

STATE_define(DC_idle)
{
	//State_Name
	DC_state_id=DC_idle;

	//State_Action
	//CALL PWM to make speed =DC_speed

	printf("DC_idle State :Speed =%d\n",DC_speed);

}


STATE_define(DC_busy)
{
	//State_Name
	DC_state_id=DC_busy;

	//State_Action
	//CALL PWM to make speed =DC_speed

	printf("DC_busy State :Speed =%d\n",DC_speed);
	DC_state=STATE(DC_idle);

}


