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

	//Asking The User to Enter 2Numbers
	printf("Enter two integers :");
	fflush(stdin);fflush(stdout);
	scanf("%d %d",&u32num1,&u32num2);

	//Printing The Sum
	printf("Sum: %d",u32num1+u32num2);

}
