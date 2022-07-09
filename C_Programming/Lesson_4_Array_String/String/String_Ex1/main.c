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
	int i =0 ,freq=0;
	char character;
	//Asking The User to Enter String
	printf("Enter a String :");
	fflush(stdin);fflush(stdout);
//	scanf("%s",text);
	gets(text);


	//Asking The User To Enter a character to Find its Freq
	printf("Enter a Character to find Frequency :");
	fflush(stdin);fflush(stdout);
	scanf("%c",&character);

	//Find Frequency of The Character
	while (text[i] !=0)
	{
		if(text[i]==character)
		{
			freq++;
		}
		i++;
	}

	//Printing The Freq
	printf("Frequency of %c = %d",character,freq);

}
