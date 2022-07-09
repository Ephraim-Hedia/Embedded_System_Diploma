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
	//The Program to Calculate Average Using Array

	//Initialization
	int n ,i ;
	float arr[100],sum=0,average;

	//Asking The User to Enter The Number of Data Elements
	printf("Enter The Number of Data :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);

	for (i = 0 ; i<n;i++)
	{
		printf("%d. Enter Number :",i+1);
		fflush(stdin);fflush(stdout);
		scanf("%f",&arr[i]);
		sum +=arr[i];
	}

	//Calculating The Average
	average =sum/n;

	//Printing The Average To The User
	printf("Average = %f",average);

}
