/*
 * main.c
 *
 *  Created on: Sep 12, 2022
 *      Author: ff
 */

#include "CA.h"

void setup()
{
	//init all The Drivers;
	//inti IRQ ....
	//init HAL US_Driver DC_Driver
	//init Block
	//Set States Pointer for each Block

	CA_state=STATE(CA_waiting);
}
int main ()
{
	volatile int i ;
	setup();

	while(1)
	{
		//Call State for each Block
		CA_state();
		for(i=0;i<50000;i++);
	}
	return 0;
}
