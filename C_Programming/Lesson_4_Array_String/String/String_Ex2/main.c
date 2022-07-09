/*
 * main.c
 *
 *  Created on: Jul 9, 2022
 *      Author: Ephraim
 */

#include "stdio.h"
#include "string.h"

void main (void)
{
	//Initialization
	char text[100];
	int i=0;


	//Asking The User to Enter String
	printf("Enter a String : ");
	fflush(stdin);fflush(stdout);
	gets(text);

	while (text[i] !=0)
	{
		i++;
	}
	printf("Length of String = %d",i);



}
