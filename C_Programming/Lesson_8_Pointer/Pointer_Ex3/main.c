/*
 * main.c
 *
 *  Created on: Aug 7, 2022
 *      Author: Ephraim
 */

#include "stdio.h"


/*
Write a program in C to print a string in reverse using a pointer
The Alphabets are :
Test Data :
Input a string : w3resource
Expected Output :
Pointer : Print a string in reverse order :
------------------------------------------------
Input a string : w3resource
Reverse of the string is : ecruoser3w
 * */
int main()
{
	int i;
	char text[20];
	char *p=text;
	printf("Enter String :");
	fflush(stdin);fflush(stdout);
	gets(text);
	printf("\n\n");

	//This Loop to Find The First Null
	for(i=0;i<20;i++)
	{
		if(text[i]=='\0')
		{
			p=&text[i]-1;
			break;
		}
	}

	printf("Reverse of The String is :");
	for(;i>0;i--)
	{
		printf("%c",*p);
		p--;
	}


	return 0;
}
