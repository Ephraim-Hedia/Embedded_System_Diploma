/*
 * main.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Ephraim
 */

#include "stdio.h"


//The program to check Vowel or Consonant
void main (void)
{
	char u8x;

	//Asking The User To Enter Character
	printf("Enter an alphabet :");
	fflush(stdin);fflush(stdout);
	scanf("%c",&u8x);

	//Check if Vowel or Consonant
	switch (u8x)
	{
		case 'a':
		case 'A':
		case 'i':
		case 'I':
		case 'u':
		case 'U':
		case 'e':
		case 'E':
		case 'o':
		case 'O':
			printf("%c is a vowel\n",u8x);
			break;
		default:
			printf("%c is a Consonant\n",u8x);
			break;

	}

}
