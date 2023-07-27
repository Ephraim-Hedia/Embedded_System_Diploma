/*
 * main.c
 *
 *  Created on: Jul 30, 2022
 *      Author: Ephraim
 */
#include "stdio.h"
#include "string.h"
#include "conio.h"


/*
 * EX4: C Program to Store Information Of Students using Structure
 * In this program , a structure (student) is created which
 * contains name , roll and marks as its data member .
 * Then , an array of structure of 10 elements is created ,
 * Then , data(name , roll and marks) for 10 elements is asked to
 * user and stored in array of structure . Finally , the data
 * entered by the user is displayed
 *
 *
 * OUTPUT :
 *
 * Enter Information of Students :
 *
 * For roll number 1
 * Enter Name :Tom
 * Enter marks :98
 *
 *
 * For roll number 2
 * Enter Name :Jerry
 * Enter marks :89
 *  .
 *  .
 *  .
 *  .
 *
 *
 *  Displaying Information of Students
 *
 *  Information for roll number 1 :
 *  Name	: Tom
 *  Marks 	: 98
 *
 *
 */


struct Sstudent {
	int rollNumber;
	char name[20];
	int marks;
}Students[100];

int counter =0;

void read_information(void)
{

	printf("Enter information of Students :\n");
	char again;

	do
	{

		printf("For roll Number %d\n",counter+1);
		printf("Enter Name :");
		fflush(stdin);fflush(stdout);
		scanf("%s",Students[counter].name);

		printf("Enter Marks :");
		fflush(stdin);fflush(stdout);
		scanf("%d",&Students[counter].marks);
		fflush(stdin);fflush(stdout);
		printf("****************************************************\n");
		counter++;

		//Asking the User if He Want to Enter a New Data Or NO
		ask :
		printf("Do you want to add more , Press \'Y\' to Continue and Press \'N\' to Break?\n");
		fflush(stdin);fflush(stdout);
		scanf("%c",&again);
		if(again == 'y' || again == 'Y')
		{
			continue;
		}
		else if( again == 'N' || again =='n')
			break;

		else
		{
			printf("Wrong Option\n");
			fflush(stdin);fflush(stdout);
			goto ask;
		}

	}while(1);


}


void Diplay_information (void)
{
	int i ;
	printf("\n\nDisplaying Information of Students :\n");

	for (i=0;i<counter;i++)
	{
		printf("\n\nInformation For Roll %d\n",i+1);
		printf("Name 	:%s\n",Students[i].name);
		printf("Marks 	:%d\n",Students[i].marks);
	}
}
int main ()
{
	read_information();
	Diplay_information();
	return 0;
}
