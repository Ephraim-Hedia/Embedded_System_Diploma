/*
 * main.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Ephraim
 */

#include "stdio.h"
void main (void)
{

	int u32num;
	//Asking The User To Enter Number
	printf("Enter an integer you want to check :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&u32num);

	if (u32num %2 ==0)
	{
		printf("%d is even",u32num);
	}
	else
	{
		printf("%d is odd",u32num);
	}
}

