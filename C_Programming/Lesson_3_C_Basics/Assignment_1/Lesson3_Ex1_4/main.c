/*
 * main.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Ephraim
 */

//Write C Program to Multiply two Floating Point Numbers
#include "stdio.h"

void main (void)
{
	float num1,num2;

	//Asking The User to Enter Two Floating Numbers
	printf("Enter two numbers:");
	fflush(stdin);fflush(stdout);
	scanf("%f %f",&num1,&num2);

	//Printing The Result
	printf("Product: %f",num1*num2);
}
