/*
 * main.c
 *
 *  Created on: Jul 21, 2023
 *      Author: Ephraim
 */


#include "Student_Mangement_System.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{

	char Local_u8CustomerChoice =0;
	char temp[2];
	DPRINTF("Welcome to the Student Management System\n");


	/*---------------------------------------------------------------*/
	//Initialization of the System and Database
	SMS_voidInit();
	/*---------------------------------------------------------------*/




	while(1)
	{
		DPRINTF("\n-----------------------------------------------");
		DPRINTF("\nChoose The Task that you want to perform :\n");
		DPRINTF("1.  Add Student Details Manually \n");
		DPRINTF("2.  Add Student Details From Text File \n");
		DPRINTF("3.  Find The Student Details By the Roll Number \n");
		DPRINTF("4.  Find The Student Details By the First Name \n");
		DPRINTF("5.  Find The Student Details By the Course ID \n");
		DPRINTF("6.  Find The Total Number of Students \n");
		DPRINTF("7.  Delete the Student Details By Roll Number \n");
		DPRINTF("8.  Update the Student Details By Roll Number \n");
		DPRINTF("9.  Show all Information \n");
		DPRINTF("10. To Exit \n");
		DPRINTF("-----------------------------------------------\n");
		DPRINTF("Enter Your Choice to Perform the Task:");

		gets(temp);
		Local_u8CustomerChoice=atoi(temp);

		switch(Local_u8CustomerChoice)
		{
		case 1:
			SMS_voidAddStudentManually();
			break;
		case 2:
			SMS_voidAddStudentUsingTextFile();
			break;
		case 3:
			SMS_voidFindStudentUsingRollNumber();
			break;
		case 4:
			SMS_voidFindStudentUsingFirstName();
			break;
		case 5:
			SMS_voidFindStudentUsingCourseID();
			break;
		case 6:
			SMS_voidFindTotalStudentsNumber();
			break;
		case 7:
			SMS_voidDeleteStudent();
			break;
		case 8:
			SMS_voidUpdateStudent();
			break;
		case 9:
			SMS_voidShowAll();
			break;
		case 10 :
			break;
		default:
			break;
		}


	}

	return 0;
}
