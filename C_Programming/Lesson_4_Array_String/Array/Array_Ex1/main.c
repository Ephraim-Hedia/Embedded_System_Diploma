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
	//Sum of Two Matrix

	//Initialization
	int arr1[2][2];
	int arr2[2][2];
	int i,j;

	//Asking The User to Enter Elements of Array_1
	printf("Enter The Elements of 1st matrix \n");


	for (i=0;i<2;i++)
	{
		for (j=0;j<2;j++)
		{
			printf("Enter a%d%d = ",i+1,j+1);
			fflush(stdin);fflush(stdout);
			scanf("%d",&arr1[i][j]);
		}
	}

	//Asking The User to Enter Elements of Array_2
	printf("Enter The Elements of 2st matrix \n");


	for (i=0;i<2;i++)
	{
		for (j=0;j<2;j++)
		{
			printf("Enter b%d%d = ",i+1,j+1);
			fflush(stdin);fflush(stdout);
			scanf("%d",&arr2[i][j]);
		}
	}

	//Printing The sum of The Two Matrix
	printf("Sum of Matrix : \n");

	for (i=0;i<2;i++)
		{
			for (j=0;j<2;j++)
			{
				printf("%d \t",arr1[i][j]+arr2[i][j]);

			}
			printf("\n");
		}






}
