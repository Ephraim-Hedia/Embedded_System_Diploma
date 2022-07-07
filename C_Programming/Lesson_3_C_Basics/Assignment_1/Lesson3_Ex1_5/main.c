/*
 * main.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Ephraim
 */
#include "stdio.h"


void main (void)
{
	char u8x;

	//Asking The User to Enter a Character
	printf("Enter a character: ");
	fflush(stdin);fflush(stdout);
	scanf("%c",&u8x);

	//Printing The ASCII Value of The Character
	printf("ASCII value of %c = %d",u8x,u8x);


}
