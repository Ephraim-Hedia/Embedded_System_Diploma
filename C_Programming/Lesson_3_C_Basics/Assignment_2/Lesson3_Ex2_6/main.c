/*
 * main.c
 *
 *  Created on: Jul 7, 2022
 *      Author: Ephraim
 */

#include "stdio.h"

void main (void)
{
	int u32Number,i,sum=0;

	//Asking The User to Enter Number
	printf("Please Enter an Integer Number :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&u32Number);

	//Calculate The Sum From 0 to u32Number

	for(i=1;i<=u32Number;i++)
	{
		sum +=i;
	}

	//Printing The Sum To the User
	printf("The Sum = %d",sum);
}
