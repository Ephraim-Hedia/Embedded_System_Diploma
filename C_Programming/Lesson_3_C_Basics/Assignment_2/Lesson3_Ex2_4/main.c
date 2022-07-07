/*
 * main.c
 *
 *  Created on: Jul 7, 2022
 *      Author: Ephraim
 */
#include "stdio.h"


void main (void )
{
	float f32Number;

	//Asking The User To Enter a Number
	printf("Please Enter a Number :");
	fflush(stdin);fflush(stdout);
	scanf("%f",&f32Number);

	//Check if The Number Positive or Negative of Zero
	if (f32Number >0)
	{
		printf("%f is Positive ",f32Number);
	}
	else if (f32Number <0)
	{
		printf("%f is Negative ",f32Number);
	}
	else
	{
		printf("%f is Zero",f32Number);
	}
}
