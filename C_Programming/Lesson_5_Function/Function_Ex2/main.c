/*
 * main.c
 *
 *  Created on: Jul 15, 2022
 *      Author: Ephraim
 */

#include "stdio.h"

int factorial (int x)
{

	if(x>0)
		return x* factorial(x-1);
	else
		return 1;
}

void main (void)
{
	printf("This Program To Calculate Factorial number Using Recursion\n\n");
	//Asking The User to Enter Positive Number
	int num,Factorial_Number;
	printf("Enter a Positive Number :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&num);

	//This Condition if he Enter an Negative Number
	while (num <0)
	{
		printf("You Entered a Negative Number\nEnter a Positive Number :");
		fflush(stdin);fflush(stdout);
		scanf("%d",&num);
	}

	//Calculate The Factorial and Print The Result
	Factorial_Number =factorial(num);
	printf("Factorial of %d = %d",num,Factorial_Number);
}
