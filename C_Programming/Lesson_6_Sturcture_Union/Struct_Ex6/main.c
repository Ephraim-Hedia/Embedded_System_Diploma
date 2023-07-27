/*
 * main.c
 *
 *  Created on: Jul 30, 2022
 *      Author: Ephraim
 */

#include "stdio.h"
#include "string.h"

union job{
	char name [32];
	float salary;
	int Worker_no;
}u;

struct job1{
	char name[32];
	float salary;
	int Worker_No;
}s;

int main ()
{
	printf("Size of Union=%d\n",sizeof(u));
	printf("Size of Struct=%d\n",sizeof(s));
	return 0;
}
