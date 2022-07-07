/*
 * main.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Ephraim
 */

#include "stdio.h"

void main (void)
{
	int u32num1,u32num2;

	//Ask User to Enter Two Integer Number
	//Enter The First Number
	printf("Enter value of a :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&u32num1);
	//Enter The Second Number
	printf("Enter value of b :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&u32num2);

	//Swapping Processing
	u32num1=u32num1*u32num2;
	u32num2=u32num1/u32num2;
	u32num1=u32num1/u32num2;

	//Printing Number After Swapping
	printf("After swapping, value of a=%d\nAfter swapping, value of b=%d",u32num1,u32num2);

}
