/*
 * main.c
 *
 *  Created on: Aug 7, 2022
 *      Author: Ephraim
 */

#include "stdio.h"

/*
Write a program in C to show a pointer to an array which contents
are pointer to structure.
Expected Output :
Exmployee Name : Alex
Employee ID : 1002
 */


struct SEmployee
{
	char name[20] ;
	int id ;
};



int main()
{
	struct SEmployee employee1={"Alex",1002} ,employee2={"Ephraim",1003},employee3={"Anton",1004};

	struct SEmployee *pstruct[3] ={&employee1,&employee2,&employee3};

	struct SEmployee **p=pstruct;

	printf("Exmployee Name :%s\n",p[1]->name);
	printf("Employee ID :%d \n",p[1]->id);

	//Another Method
	printf("Exmployee Name :%s\n",(*(p+2))->name);
	printf("Employee ID :%d \n",(*(p+2))->id);

	return 0;
}
