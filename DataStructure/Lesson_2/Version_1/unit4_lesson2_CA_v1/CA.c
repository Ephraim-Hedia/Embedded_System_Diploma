/*
 * CA.c
 *
 *  Created on: Sep 12, 2022
 *      Author: ff
 */

#include "CA.h"
//Variables
int CA_speed =0;
int CA_distance =0;
int CA_threshold =50;


//STATE Pointer to Function
void (*CA_state )();
int US_GET_distance_rondom(int l,int r);

STATE_define(CA_waiting)
{
	//State_Name
	CA_state_id=CA_waiting;

	//State_Action
	CA_speed=0;

	//Event_Check
	//US_GET_Distance(CA_distance)
	CA_distance=US_GET_distance_rondom(45,55);

	(CA_distance <=CA_threshold)?(CA_state=STATE(CA_waiting)):(CA_state=STATE(CA_driving));

	printf("CA_driving State : Distance =%d \tSpeed =%d\n",CA_distance,CA_speed);

}


STATE_define(CA_driving)
{
	//State_Name
	CA_state_id=CA_driving;

	//State_Action
	CA_speed=30;

	//Event_Check
	//US_GET_Distance(CA_distance)
	CA_distance=US_GET_distance_rondom(45,55);
	(CA_distance <= CA_threshold)?(CA_state=STATE(CA_waiting)):(CA_state=STATE(CA_driving));

	printf("CA_driving State : Distance =%d \tSpeed =%d\n",CA_distance,CA_speed);
}

int US_GET_distance_rondom(int l,int r)
{
	int rand_num;
	rand_num = (rand() % (r - l + 1)) + l;
	return rand_num;

}
