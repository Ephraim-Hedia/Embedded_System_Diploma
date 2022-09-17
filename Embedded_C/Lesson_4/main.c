


#include "stdint.h"
#define SYSCTL_RCGC2_R 		*((volatile unsigned long*)0x400FE108)
#define GPIO_PORTF_DIR_R 	*((volatile unsigned long*)0x040025400)
#define GPIO_PORTF_DEN_R 	*((volatile unsigned long*)0x04002551C)
#define GPIO_PORTF_DATA_R 	*((volatile unsigned long*)0x0400253FC)


int main()
{	
	volatile unsigned long delay_count;
	SYSCTL_RCGC2_R=0x20;
	//Delay to make sure GPIOF is up to and running 
	for (delay_count ;delay_count<200;delay_count++ );
	
	GPIO_PORTF_DIR_R |= (1<<3); //Direction is Output fot pin 3 Port F 
	GPIO_PORTF_DEN_R |= (1<<3);
	
	
	while(1)
	{
		GPIO_PORTF_DATA_R |=(1<<3);
		for (delay_count ;delay_count<20000;delay_count++ );
		GPIO_PORTF_DATA_R &=~(1<<3);
		for (delay_count ;delay_count<20000;delay_count++ );
	}
	return 0;
}