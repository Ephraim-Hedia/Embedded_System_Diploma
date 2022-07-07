/*
 * main.c
 *
 *  Created on: Jul 7, 2022
 *      Author: Ephraim
 */
#include "stdio.h"

void main (void)
{
	int u32Number ,i,fact=1;

	//asking The User to Enter an Integer Number
	printf("Please Enter an Integer Number :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&u32Number);

	//Calculate The Factorial to u32Number
	if (u32Number >0)
	{
		for (i=1;i<=u32Number;i++)
		{
			fact *=i;
		}
		//Printing The Result to The User
		printf("The Factorial = %d",fact);
	}
	else
	{
		printf("Error!!! Factorial to Negative Number doesn't Exist");
	}



}

