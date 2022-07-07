/*
 * main.c
 *
 *  Created on: Jul 7, 2022
 *      Author: Ephraim
 */

#include "stdio.h"
void main (void)
{
	char u8Operator;
	float f32Operand1,f32Operand2;

	//Asking The User to Enter Operator
	printf("Enter Operator either + , - , * or divide :");
	fflush(stdin);fflush(stdout);
	scanf("%c",&u8Operator);

	//Asking The User to Enter Operands
	printf("Enter two Operands :");
	fflush(stdin);fflush(stdout);
	scanf("%f %f",&f32Operand1,&f32Operand2);

	switch (u8Operator)
	{
	case '+' :
		printf("%f + %f = %f",f32Operand1,f32Operand2,f32Operand1+f32Operand2);
		break;
	case '-' :
		printf("%f - %f = %f",f32Operand1,f32Operand2,f32Operand1-f32Operand2);
		break;
	case '*' :
		printf("%f * %f = %f",f32Operand1,f32Operand2,f32Operand1*f32Operand2);
		break;
	case '/' :
		printf("%f / %f = %f",f32Operand1,f32Operand2,f32Operand1/f32Operand2);
		break;
	default :
		printf("The Operator isn't Correct");

	}



}
