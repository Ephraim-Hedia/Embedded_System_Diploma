/*
 * main.c
 *
 *  Created on: Jul 30, 2022
 *      Author: Ephraim
 */
#include "stdio.h"
#include "string.h"

/*
 * EX5:C programming to find area of a Circle , passing arguments
 * to macros
 *
 * OUTPUT
 *
 * Enter the radius :3
 * Area =28.27
 */


#define PI 3.14
#define area(r)	(PI*(r)*(r))


int main ()
{
	int Local_u32radius ;
	float Local_f32area ;

	//Asking the User to Enter the Raduis
	printf("Enter the Radius :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&Local_u32radius);

	//Calculating the area Using Macros
	Local_f32area=area(Local_u32radius);

	//Display the Result to the User
	fflush(stdin);fflush(stdout);
	printf("Area=%0.2f",Local_f32area);
	return 0;
}
