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
	int n,inserted_num,num_location;
	int arr[100];
	int i ;

	//Asking The User About The number Of Element
	printf("Enter Number of Elements :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);

	//Creating Array with values 1,2,3,4,5,.... till n Element
	for (i=0;i<n;i++)
	{
		arr[i]=i+1;
	}

	//Asking The User About The Element will be Inserted
	printf("Enter The Element to be Inserted :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&inserted_num);

	//Asking The User About The Location of Inserted Number
	printf("Enter The Location :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&num_location);

	//Shifting The Number to the left till The Location of Inserted Number
	for (i=n;i>num_location;i--)
	{
		arr[i]=arr[i-1];
	}

	//Insert The Number
	arr[num_location]=inserted_num;

	//Print The Array After The Insertion
	for (i=0;i<=n;i++)
	{
		printf("%d\t",arr[i]);
	}



}
