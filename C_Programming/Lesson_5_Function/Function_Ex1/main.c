/*
 * main.c
 *
 *  Created on: Jul 15, 2022
 *      Author: Ephraim
 */


#include "stdio.h"

void PrimeNumber(int x , int y)
{
	int i ,j,flag=0;

	printf("Prime Number Between %d and %d are :",x,y);

	for (i =x;i<=y;i++) 	// This Iteration With range of The Numbers The User Choose
	{
		flag=0;				//this step to clear Flag
		for (j=2;j<i;j++)	//This Iteration with numbers we will divide into,with range of 2 to the number we check
		{
			if (i%j == 0)	//if The number not Prime make The Flag =1
			{
				flag=1;
			}
		}
		if (flag==0)		//if The Flag still = 0 ,So The Number is Prime and print it
		{
			printf("%d\t ",i);
		}
	}
}




void main (void)
{
	int num1,num2;
	printf("******This Program to Print Prime Numbers Between Two Intervals By Making User-defined Function******\n");


	//Asking The User to Enter Two Number and pass them By value to func
	printf("Enter Two Number :");
	fflush(stdin);fflush(stdout);
	scanf("%d %d",&num1,&num2);
	PrimeNumber(num1 , num2);


}
