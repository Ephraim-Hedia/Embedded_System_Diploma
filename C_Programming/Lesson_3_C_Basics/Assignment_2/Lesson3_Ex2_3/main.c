/*
 * main.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Ephraim
 */
#include "stdio.h"

void main (void)
{

	int u32num1,u32num2,u32num3;

	//Asking The User to Enter Three Numbers
	//The first Number
	printf("Please Enter Number 1 :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&u32num1);
	//The Second Number
	printf("Please Enter Number 2 :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&u32num2);
	//The Third Number
	printf("Please Enter Number 3 :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&u32num3);

	//Check about the Largest Number and Print it
	if (u32num1>u32num2 && u32num1>u32num3)
	{
		printf("%d is The Largest Number ",u32num1);
	}
	else if (u32num2>u32num1 && u32num2>u32num3)
	{
		printf("%d is The Largest Number ",u32num2);
	}
	else
	{
		printf("%d is The Largest Number ",u32num3);
	}


}

