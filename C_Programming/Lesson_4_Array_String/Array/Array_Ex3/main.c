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
	int arr[100][100];
	int r,c,i,j;

	//Asking The User to Enter The Size of The matrix
	printf("Enter Rows and Columns of matrix :");
	fflush(stdin);fflush(stdout);
	scanf("%d %d",&r,&c);


	//Asking The User to Enter The Elements of The Matrix
	printf("Enter The Elements of The matrix \n");

	for (i=0;i<r;i++)
	{
		for (j=0;j<c;j++)
		{
			printf("Enter Element a%d%d :",i+1,j+1);
			fflush(stdin);fflush(stdout);
			scanf("%d",&arr[i][j]);
		}
	}
	//Printing The Entered Matrix
	printf("Entered Matrix:\n");
	for (i=0;i<r;i++)
	{
		for (j=0;j<c;j++)
		{
			printf("%d\t",arr[i][j]);
		}
		printf("\n");
	}
	//Printing The Transpose
	printf("Transpose of Matrix:\n");
	for (i=0;i<c;i++)
	{
		for (j=0;j<r;j++)
		{
			printf("%d\t",arr[j][i]);
		}
		printf("\n");
	}
}


