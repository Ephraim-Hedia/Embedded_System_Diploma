/*
 * main.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Ephraim
 */



//Write Source Code to Swap Two Numbers
#include "stdio.h"


void main (void)
{
	float f32num1,f32num2,f32num3;

	//Asking The User to Enter Two float Value
	//The first Number
	printf("Enter value of a:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&f32num1);
	//The Second Number
	printf("Enter value of b:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&f32num2);

	//Swapping Processing
	f32num3=f32num1;
	f32num1=f32num2;
	f32num2=f32num3;

	//Printing The Two Number After Swapping
	printf("After swapping, value of a =%f\nAfter swapping, value of b= %f",f32num1,f32num2);

}
