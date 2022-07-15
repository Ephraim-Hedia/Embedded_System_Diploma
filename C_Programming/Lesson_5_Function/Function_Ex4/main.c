/*
 * main.c
 *
 *  Created on: Jul 15, 2022
 *      Author: Ephraim
 */
#include "stdio.h"
int Power_Number(int Base,int Power)
{
	if(Power>=1) //if Power Still >= than 1 , So return base*base*base*.... till The power =0
	{
		return Base*Power_Number(Base,Power-1);
	}
	else		//If The Power Become Equal 0 return 1
		return 1;
}
void main (void)
{
	int base_Number ,power_Number,result_Number;

	printf("This Program to Calculate The result of The Power of The Number Using Recursion \n\n");

	printf("Enter Base Number :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&base_Number);

	printf("Enter Power Number(Positive Number) :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&power_Number);

	while(power_Number <0)
	{
		printf("You Entered Negative Number ,Enter Power Number(Positive Number) :");
		fflush(stdin);fflush(stdout);
		scanf("%d",&power_Number);
	}
	result_Number=Power_Number(base_Number,power_Number);

	printf("%d^%d =%d",base_Number,power_Number,result_Number);

}

