/*
 * main.c
 *
 *  Created on: Aug 7, 2022
 *      Author: Ephraim
 */

#include "stdio.h"


/*
Write a program in C to print the elements of an array in reverse
order.
*/
int main ()
{
	unsigned int Local_u32NumberofElementOfArray,arr[50],Local_u32Counter ,reverseArr[50];
	char Local_s8TempVal[3];
	unsigned int * pOfarr = NULL;
	int i =0;


	//Asking the User to Enter the Number of Element in The Array
	fflush(stdin);fflush(stdout);
	printf("Enter Number of Elements of Array [Max 50]:");
	fflush(stdin);fflush(stdout);
	gets(Local_s8TempVal);
	Local_u32NumberofElementOfArray = atoi(Local_s8TempVal);


	//Gets the Elements form the user
	for(Local_u32Counter = 0 ; Local_u32Counter <Local_u32NumberofElementOfArray;Local_u32Counter++)
	{
		fflush(stdin);fflush(stdout);
		printf("Enter Element No.%d :",Local_u32Counter+1);
		fflush(stdin);fflush(stdout);
		gets(Local_s8TempVal);
		arr[Local_u32Counter]=atoi(Local_s8TempVal);
	}

	//Put the Pointer Equal The Address of Last Element of the array
	pOfarr = &arr[Local_u32Counter-1];


	//Store the Array in Reverse Mode in Another Array
	for(;Local_u32Counter>0;Local_u32Counter--)
	{
		reverseArr[i]=*pOfarr;
		i++;
		pOfarr--;
	}


	//Print the Reverse Array
	fflush(stdin);fflush(stdout);
	printf("The Array After Reversing :\n");
	fflush(stdin);fflush(stdout);
	for(Local_u32Counter = 0 ; Local_u32Counter <Local_u32NumberofElementOfArray;Local_u32Counter++)
	{
		fflush(stdin);fflush(stdout);
		printf("%d",reverseArr[Local_u32Counter]);
	}

	return 0;
}
