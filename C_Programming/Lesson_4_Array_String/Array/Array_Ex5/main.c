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

	//initialization
	int n ,search_num;
	int arr[100];
	int i ;

	//Asking The Enter The Number of Elements
	printf("Enter The Number of Elements :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);

	//Creating Array its Values is 11,22,33,44,....  with n Elements
	for (i=0;i<n;i++)
	{
		arr[i]=11+11*i;
	}

	//Asking The User to Enter The Value Search about
	printf("Enter The Element to be Searched :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&search_num);

	//Searching
	for (i=0;i<n;i++)
	{
		if(arr[i]==search_num)
			break;
	}
	if (i==n)
	{
		printf("Not Found \n");
	}
	else
	{
		printf("Number Found at The Location = %d",i+1);
	}

}
