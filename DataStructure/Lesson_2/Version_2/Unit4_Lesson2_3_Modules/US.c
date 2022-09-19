/*
 * US.c
 *
 *  Created on: Sep 12, 2022
 *      Author: ff
 */

#include "US.h"
//Variables
int US_distance =0;



//STATE Pointer to Function
void (*US_state )();
int US_GET_distance_rondom(int l,int r);



void US_init()
{
	//Initialize US Driver
	printf("US init \n");
}

STATE_define(US_busy)
{
	//State_Name
	US_state_id=US_busy;

	//State_Action
	US_distance=US_GET_distance_rondom(45,55);

	printf("\nUS_busy State : Distance =%d\n",US_distance);
	US_Set_distance(US_distance);
	US_state=STATE(US_busy);
}

int US_GET_distance_rondom(int l,int r)
{

	int rand_num = (rand() % (r - l + 1)) + l;
	return rand_num;

}
