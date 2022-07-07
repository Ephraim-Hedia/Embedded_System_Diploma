/*
 * main.c
 *
 *  Created on: Jul 7, 2022
 *      Author: Ephraim
 */
#include "stdio.h"

void main (void)
{
	char u8character;

	//Asking The User to Enter a character
	printf("Please Enter a Character :");
	fflush(stdin);fflush(stdout);
	scanf("%c",&u8character);

	//check if The character is alphabet of not
	if ((u8character >= 'a' && u8character <='z' ) || (u8character >= 'A' && u8character <='Z' ) )
	{
		printf("%c is alphabet",u8character);

	}
	else
	{
		printf("%c isn't alphabet",u8character);
	}
}
