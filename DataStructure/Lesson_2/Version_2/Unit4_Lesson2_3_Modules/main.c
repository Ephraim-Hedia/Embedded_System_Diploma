/*
 * main.c
 *
 *  Created on: Sep 12, 2022
 *      Author: ff
 */

#include "CA.h"
#include "US.h"
#include "DC.h"

void setup()
{
	//init all The Drivers;
	//inti IRQ ....
	//init HAL US_Driver DC_Driver
	//init Block
	US_init();
	DC_init();
	//Set States Pointer for each Block
	US_state=STATE(US_busy);
	CA_state=STATE(CA_waiting);
	DC_state=STATE(DC_idle);
}
int main ()
{
	//volatile int i ;
	setup();

	while(1)
	{
		//Call State for each Block
		US_state();
		CA_state();
		DC_state();
//		for(i=0;i<50000;i++);
	}
	return 0;
}
