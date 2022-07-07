/*

 * main.c
 *
 *  Created on: Jul 4, 2022
 *      Author: Ephraim
 */

#include "stdio.h"

void  main (void)
{
	int num;

	//Ask The User to Enter an Integer Number
	printf("Enter a integer: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&num);

	//Printing The Number Entered by The User
	printf("\n\rYou entered: %d",num);



}
