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
	char reverse_text[100];
	int length,len;
	int i =0;

	//Asking The User to Enter a String
	printf("Enter The String 	:");
	fflush(stdin);fflush(stdout);
	gets(text);

	//Get String Length
	length =strlen(text);
	len=length-1;

	//Reversing The Array
	for (i=0 ;i<length ;i++)
	{
		reverse_text[len]=text[i];
		len--;
	}
	//Put 0 in The End of Array
	reverse_text[length]=0;
	//Printing The Reversing String
	printf("Reverse String is : %s",reverse_text);




}
