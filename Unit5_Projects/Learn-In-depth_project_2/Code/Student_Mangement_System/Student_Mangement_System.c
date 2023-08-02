/*
 * Student_Mangement_System.c
 *
 *  Created on: Jul 21, 2023
 *      Author: Ephraim
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student_Mangement_System.h"
#include "Student_Mangement_Database.h"
#include "Student_Mangement_Queue.h"

typedef enum
{
	SMS_INPUT_SYNTAX_ERROR,
	SMS_INPUT_NO_ERROR
}Syntax_Error_t;


/*
 * ==========================================================================================
 * 									Generic Macros
 * ==========================================================================================
 */
#define DATABASESIZE	50

/*
 * ==========================================================================================
 * 									Generic Functions
 * ==========================================================================================
 */


static Syntax_Error_t SMS_voidGetRollNumberFromTheUser(int * Copy_u32RollNumber)
{
	char temp[20];
	//Asking the User to Enter ROll Number
	DPRINTF("Enter The Roll Number [1 ~ 2000]:");
	gets(temp);
	*Copy_u32RollNumber =atoi(temp);
	if((*Copy_u32RollNumber < 1) || (*Copy_u32RollNumber >2000))
		return SMS_INPUT_SYNTAX_ERROR;

	return SMS_INPUT_NO_ERROR;
}
static Syntax_Error_t SMS_voidGetNameFromTheUser(char *Copy_u8Name ,char * Copy_u8Choice)
{

	char temp[20];
	DPRINTF("Enter The %s of the Student [Max 20 Char]:",Copy_u8Choice);
	gets(temp);
	strcpy(Copy_u8Name,temp);
	if(strlen(Copy_u8Name)>20)
		return SMS_INPUT_SYNTAX_ERROR;
	return SMS_INPUT_NO_ERROR;
}

static Syntax_Error_t SMS_voidGetGPAFromTheUser(float *Copy_fGPA)
{
	//Asking the User to Enter GPA
	DPRINTF("Enter The GPA you obtained [0 ~ 5]:");
	scanf("%f",Copy_fGPA);
	if((*Copy_fGPA < 0) || (*Copy_fGPA >5))
		return SMS_INPUT_SYNTAX_ERROR;

	return SMS_INPUT_NO_ERROR;
}

static Syntax_Error_t SMS_voidGetCourseIDsFromTheUser(int *Copy_u32CourseIDs)
{
	int i ;
	char temp[20];
	//Asking the User to Enter Courses information
	for (i = 0 ; i <5 ; i++)
	{
		DPRINTF("Course %d ID :",i+1);
		gets(temp);
		*Copy_u32CourseIDs =atoi(temp);
		Copy_u32CourseIDs++ ;
	}

	return SMS_INPUT_NO_ERROR;
}


static void SMS_voidGetInformationFromTheUser(sStudentDetail_t* StudentInfo)
{

	DPRINTF("---------------------------\n");
	DPRINTF("Add The Students Details : \n");
	DPRINTF("---------------------------\n");

	//Asking the User to Enter ROll Number
	while(SMS_voidGetRollNumberFromTheUser(&(StudentInfo->RollNumber))==SMS_INPUT_SYNTAX_ERROR)
	{
		DPRINTF("You Enter Wrong Syntax\n");
	}

	//Asking the User to Enter First Name
	while(SMS_voidGetNameFromTheUser(StudentInfo->FirstName,"First Name")==SMS_INPUT_SYNTAX_ERROR)
	{
		DPRINTF("You Enter Wrong Syntax\n");
	}

	//Asking the User to Enter Last Name
	while(SMS_voidGetNameFromTheUser(StudentInfo->LastName ,"Last Name")==SMS_INPUT_SYNTAX_ERROR)
	{
		DPRINTF("You Enter Wrong Syntax\n");
	}

	//Asking the User to Enter GPA
	while(SMS_voidGetGPAFromTheUser(&(StudentInfo->GPA))==SMS_INPUT_SYNTAX_ERROR)
	{
		DPRINTF("You Enter Wrong Syntax\n");
	}

	//Asking the User to Enter Courses information
	while(SMS_voidGetCourseIDsFromTheUser(StudentInfo->CourseIDs)==SMS_INPUT_SYNTAX_ERROR)
	{
		DPRINTF("You Enter Wrong Syntax\n");
	}
}















/*
 * ==========================================================================================
 * 								APIs Function Definitions
 * ==========================================================================================
 */


/*==========================================================================================
 * @Fn						- 	SMS_voidInit
 * @brief					- 	Initialize the Database of the System
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function Prints if the Function Successfully
 * 								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidInit(void)
{
	FIFO_Buf_Status FIFO_error;
	FIFO_error =SMD_InitDatabase();
	switch(FIFO_error)
		{
		case FIFO_no_error:
			DPRINTF("-------------------------------------------\n");
			DPRINTF("[INFO] The Database Initialize Successfully\n");
			DPRINTF("-------------------------------------------\n");
			break;
		case FIFO_null:
			DPRINTF("-------------------------------------------\n");
			DPRINTF("[ERROR] The Database NOT READY 			\n");
			DPRINTF("-------------------------------------------\n");
			break;
		default :
			break;

		}
}




/*==========================================================================================
 * @Fn						-	SMS_voidAddStudentUsingTextFile
 * @brief					-	Adding Student Data To the Database Using Text File (Must Every Student Have A unique Roll Number)
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function Prints if the Function Successfully
 * 								OR if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidAddStudentUsingTextFile(void)
{
	SMD_Error_t SMD_error ;
	sStudentDetail_t tempStudentBuff[DATABASESIZE];//Define the Size of Array with the Worst Case --> Text file Have All The database Size
	unsigned int Local_u32NumberOfRecords ;
	int i =0;
	int Local_u32TotalStudentNumber=0;

	//Reading from File
	SMD_error = SMD_AddStudentFromTextFile(tempStudentBuff , &Local_u32NumberOfRecords);

	switch (SMD_error)
	{
	case SMD_FILE_NOT_OPEN:
		DPRINTF("[ERROR] File Not OPEN\n")
		break;
	case SMD_FILE_WRONG_FORMAT:
		DPRINTF("[ERROR] Wrong File Format , Please Make Sure You Write a Correct Foramt\n")
		break;
	case SMD_FILE_READING_ERROR:
		DPRINTF("[ERROR] File Reading Error\n")
		break;
	case SMD_NO_ERROR:
		DPRINTF("[INFO] File Reading Done\n")
		break;
	default :
		break;
	}

	//Treatment with the Database
	DPRINTF("-------------------------------------------- \n");
	for (i = 0 ; i <Local_u32NumberOfRecords ; i++)
	{
		SMD_error =SMD_AddStudent(&tempStudentBuff[i]);
		switch(SMD_error)
		{
		case SMD_NO_ERROR:
			DPRINTF("[INFO] Roll Number %d is Added Successfully \n",tempStudentBuff[i].RollNumber);
			break;
		case SMD_DATABASE_ERROR:
			DPRINTF("[ERROR] Database Error \n");
			break;
		case SMD_STUDENT_DATABASE_FULL:
			DPRINTF("[ERROR] The Database is FULL \n");
			break;
		case SMD_REPEATED_ROLL_NUMBER :
			DPRINTF("[ERROR] Roll Number %d is Already Taken \n",tempStudentBuff[i].RollNumber);
			break;
		default :
			break;
		}
	}
	DPRINTF("-------------------------------------------- \n");
	SMD_FindTotalStudentsNumber(&Local_u32TotalStudentNumber);
	// Final Result
	DPRINTF("-------------------------------------------- \n");
	DPRINTF("[INFO] The Total Number of Student is %d     \n",Local_u32TotalStudentNumber);
	DPRINTF("[INFO] You Can add up to %d Student          \n",DATABASESIZE);
	DPRINTF("[INFO] You Can add %d more  Student          \n",DATABASESIZE-Local_u32TotalStudentNumber);
}






/*==========================================================================================
 * @Fn						-	SMS_voidAddStudentManually
 * @brief					-	Adding Student Data to the Database Manually (Must Every Student Have A unique Roll Number)
 * 								Asking the User to Enter Student Data from Terminal
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function Prints if the Function Added the Student Data Successfully
 *								OR if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidAddStudentManually(void)
{
	SMD_Error_t SMD_error;
	int Local_u32TotalStudentNumber=0;
	sStudentDetail_t tempStudent ;

	//Get the Information From the User to Add the Student in the Database
	SMS_voidGetInformationFromTheUser(&tempStudent);

	//Treatment with the Database
	SMD_error=SMD_AddStudent(&tempStudent);
	SMD_FindTotalStudentsNumber(&Local_u32TotalStudentNumber);

	// Final Result
	switch(SMD_error)
	{
	case SMD_NO_ERROR:

		DPRINTF("[INFO] Student Details is added Successfully \n");
		DPRINTF("-------------------------------------------- \n");
		DPRINTF("[INFO] The Total Number of Student is %d     \n",Local_u32TotalStudentNumber);
		DPRINTF("[INFO] You Can add up to %d Student          \n",DATABASESIZE);
		DPRINTF("[INFO] You Can add %d more  Student          \n",DATABASESIZE-Local_u32TotalStudentNumber);
		break;
	case SMD_DATABASE_ERROR:
		DPRINTF("[ERROR] Student Details NOT Added Successfully \n");
		DPRINTF("[ERROR] There is Database Error \n");
		break;
	case SMD_STUDENT_DATABASE_FULL:
			DPRINTF("[ERROR] Student Details NOT Added Successfully \n");
			DPRINTF("[ERROR] Student Database is FULL \n");
			break;
	case SMD_REPEATED_ROLL_NUMBER :
		DPRINTF("-------------------------------------------- \n");
		DPRINTF("[ERROR] Roll Number %d is Already Taken \n",tempStudent.RollNumber);
		DPRINTF("-------------------------------------------- \n");
		break;
	default :
		break;
	}
}





/*==========================================================================================
 * @Fn						-	SMS_voidFindStudentUsingRollNumber
 * @brief					-	Searching About specific Roll Number and if the roll number is Exist
 * 								The function will print its Student Data
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function Prints The Student Data who has the Roll Number
 *								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidFindStudentUsingRollNumber(void)
{
	SMD_Error_t SMD_error;
	sStudentDetail_t  tempStudent;
	int Local_u32tempRollNumber ,i;
	char temp[20];

	//Asking the User to Enter the Roll Number
	DPRINTF("Enter the Roll Number of the Student :");
	gets(temp);
	Local_u32tempRollNumber =atoi(temp);

	//Check if the Roll Number is Exist
	//and if the Roll Number is Exist make the tempStudent Variable point to its Data
	SMD_error = SMD_FindStudentUsingRollNumber(Local_u32tempRollNumber,&tempStudent);

	switch(SMD_error)
	{
	case SMD_WRONG_ROLL_NUMBER:
		//if the Roll Number is no Exist
		DPRINTF("[ERROR] Roll Number %d NO FOUND",Local_u32tempRollNumber);
		break;
	case SMD_NO_ERROR:
		//if the Roll Number is exist with no error
		DPRINTF("The Student Details are :\n");
		DPRINTF("Student First Name : %s\n" ,tempStudent.FirstName);
		DPRINTF("Student Last Name : %s\n" ,tempStudent.LastName);
		DPRINTF("Student Roll Number : %d\n" ,tempStudent.RollNumber);
		DPRINTF("Student GPA : %f\n" ,tempStudent.GPA);
		for(i =0 ; i <5 ; i++)
		{
			DPRINTF("The Course ID are %d\n",tempStudent.CourseIDs[i]);
		}
		break;

	default:
		break;

	}
}





/*==========================================================================================
 * @Fn						-	SMS_voidFindStudentUsingFirstName
 * @brief					-	Searching About specific First Name and if the First Name is Exist
 * 								The function will print Student Data
 * @param[in]				-	NONE
* @retval					-	NONE
 * Note						-	The Function will Print The Students Data who have the First Name
 *								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidFindStudentUsingFirstName(void)
{
	SMD_Error_t SMD_error;
	sStudentDetail_t  tempStudent[50];
	char Local_u8tempFirstName[20];
	int i ,j,Local_u32NumberOfStudent;

	//Asking the User to Enter the First Name
	DPRINTF("Enter the First Name of the Student :");
	gets(Local_u8tempFirstName);


	//Check if The First Name is Exist
	//and if the First Name is Exist make the tempStudent Variable point to its Data
	SMD_error=SMD_FindStudentUsingFirstName(Local_u8tempFirstName,tempStudent,&Local_u32NumberOfStudent);

	switch(SMD_error)
	{
	case SMD_DATABASE_ERROR:
		DPRINTF("[ERROR] The Database NOT READY\n");
		break;
	case SMD_WRONG_FirstName:
		//if The First Name Not Exist
		DPRINTF("[ERROR] First Name %s Not Found\n",Local_u8tempFirstName);
		break;
	case SMD_NO_ERROR:
		//Print the Details if the First Name is Exist
		DPRINTF("\nThe Student Details are :\n\n");
		for (i=0;i<Local_u32NumberOfStudent;i++)
		{
			DPRINTF("Student No. %d :\n",i+1);
			DPRINTF("-----------------------------------------------\n");
			DPRINTF("Student First Name : %s\n" ,tempStudent[i].FirstName);
			DPRINTF("Student Last Name : %s\n" ,tempStudent[i].LastName);
			DPRINTF("Student Roll Number : %d\n" ,tempStudent[i].RollNumber);
			DPRINTF("Student GPA : %f\n" ,tempStudent[i].GPA);
			for(j =0 ; j <5 ; j++)
			{
				DPRINTF("The Course ID are %d\n",tempStudent[i].CourseIDs[j]);
			}
			DPRINTF("-----------------------------------------------\n");
		}
		break;
	default:
		break;
	}
}




/*==========================================================================================
 * @Fn						-	SMS_voidFindStudentUsingCourseID
 * @brief					-	Searching About specific CourseID and if the ID is Exist
 * 								The function will print Students Data who apply in this Course
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function will Print The Students Data who have the Course ID
 *								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidFindStudentUsingCourseID(void)
{

	SMD_Error_t SMD_error;

	//This Buffer We will Store in it The data of Student who Selected The Course ID
	//And the Size of tempStudentBuffer we defined is DATABASESIZE --> The Worst Case
	//Which mean All Student Selected This Course
	sStudentDetail_t tempStudentBuff[DATABASESIZE];

	int i , j;
	char Local_u8temp[20];
	int Local_u32CourseID,Local_u32NumberOfStudent;

	//Asking the User to Enter the Course ID
	DPRINTF("Enter the Course ID :");
	gets(Local_u8temp);
	Local_u32CourseID=atoi(Local_u8temp);

	SMD_error =SMD_FindStudentUsingCourseID(Local_u32CourseID,tempStudentBuff,&Local_u32NumberOfStudent);

	//Check The Database About the Course ID
	switch(SMD_error)
	{
	case SMD_NO_ERROR:
		//Print the Details Of the Students which Have The Course ID
		DPRINTF("The Student Details are :\n");
		for(i = 0 ; i <Local_u32NumberOfStudent;i++)
		{
			DPRINTF("Student No. %d :\n",i+1);
			DPRINTF("Student First Name : %s\n" ,tempStudentBuff[i].FirstName);
			DPRINTF("Student Last Name : %s\n" ,tempStudentBuff[i].LastName);
			DPRINTF("Student Roll Number : %d\n" ,tempStudentBuff[i].RollNumber);
			DPRINTF("Student GPA : %f\n" ,tempStudentBuff[i].GPA);
			for(j =0 ; j <5 ; j++)
			{
				DPRINTF("The Course ID are %d\n",tempStudentBuff[i].CourseIDs[j]);
			}
			DPRINTF("-----------------------------------------------\n");
		}

		break;
	case SMD_COURSE_ID_NOT_FOUND:
		//IF the Course ID Not Found
		DPRINTF("[ERROR] Course ID NOT FOUND\n");
		break;
	case SMD_DATABASE_ERROR:
		DPRINTF("[ERROR] The Database NOT READY\n");
		break;
	default :
		break;
	}

}






/*==========================================================================================
 * @Fn						-	SMS_voidFindTotalStudentsNumber
 * @brief					-	This function will print the Total Number of Students and The Database Size limit
 *
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function will Print The Total Students Number
 *								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidFindTotalStudentsNumber(void)
{
	SMD_Error_t SMD_error ;
	int Local_u32TotalNumberOfStudent = 0;
	//Treatment with Database
	SMD_error = SMD_FindTotalStudentsNumber(&Local_u32TotalNumberOfStudent);

	switch(SMD_error)
	{
	case SMD_DATABASE_ERROR:
		DPRINTF("[ERROR] The Database NOT READY\n");
		break;
	case SMD_STUDENT_DATABASE_EMPTY:
		DPRINTF("[ERROR] The Database is EMPTY , Try to Enter Data\n");
		break;
	case SMD_NO_ERROR:
		//Print the Number of the Student
		DPRINTF("[INFO] The Total Number of Student is %d    \n",Local_u32TotalNumberOfStudent);
		DPRINTF("[INFO] You Can add up to %d Student         \n",DATABASESIZE);
		DPRINTF("[INFO] You Can add %d more  Student         \n",DATABASESIZE-Local_u32TotalNumberOfStudent);
		break;
	default :
		break;
	}

}





/*==========================================================================================
 * @Fn						-	SMS_voidDeleteStudent
 * @brief					-	This Function Delete the Student Information form the Database
 * 								You can Select the Student you want to Delete by the Roll Number
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function will Delete the Student Data
 *								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidDeleteStudent(void)
{
	int Local_u32tempRollNumber;
	char temp[5];
	SMD_Error_t SMD_error ;

	//Asking the User to Enter The ROll Number
	DPRINTF("Enter The Roll Number which you want to Delete :");
	gets(temp);
	Local_u32tempRollNumber=atoi(temp);

	//Treatment with Database
	SMD_error = SMD_DeleteStudent(Local_u32tempRollNumber);


	//Final Results
	switch(SMD_error)
	{
	case SMD_NO_ERROR:
		//if we Found the Roll Number and the process Successfully
		DPRINTF("[INFO] The ROll Number is removed Successfully\n");
		break;
	case SMD_DATABASE_ERROR:
		DPRINTF("[ERROR] The Database NOT READY\n");
		break;
	case SMD_STUDENT_DATABASE_EMPTY:
		DPRINTF("[ERROR] The Database is EMPTY , Try to Enter Data\n");
		break;
	case SMD_WRONG_ROLL_NUMBER:
		DPRINTF("[ERROR] The ROll Number %d NOT FOUND",Local_u32tempRollNumber);
		break;
	default :
		break;
	}
}






/*==========================================================================================
 * @Fn						-	SMS_voidUpdateStudent
 * @brief					-	This Function Update the Student Information form the Database
 * 								You can Select the Student you want to Update by the Roll Number
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function will Update the Student Data
 *								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidUpdateStudent(void)
{
	int Local_u32tempRollNumber , Local_u32UserChoice;
	char temp[20];
	int i;
	SMD_Error_t SMD_error;
	sStudentDetail_t New_StudentData ;

	//Asking the User to Enter the Roll Number
	DPRINTF("Enter the Roll Number to update the entry :");
	gets(temp);
	Local_u32tempRollNumber = atoi(temp);

	DPRINTF("Which of the Following Data You Want to Change :\n");
	DPRINTF("1. First Name\n");
	DPRINTF("2. Last Name\n");
	DPRINTF("3. Roll Number\n");
	DPRINTF("4. GPA\n");
	DPRINTF("5. Courses\n");
	gets(temp);
	Local_u32UserChoice = atoi(temp);

	switch(Local_u32UserChoice)
	{
	case 1:
		DPRINTF("Enter The New First Name :");
		gets(New_StudentData.FirstName);
		break;
	case 2:
		DPRINTF("Enter The New Last Name :");
		gets(New_StudentData.LastName);
		break;
	case 3:
		DPRINTF("Enter The New Roll Number :");
		gets(temp);
		New_StudentData.RollNumber=atoi(temp);
		break;
	case 4:
		DPRINTF("Enter The New GPA :");
		scanf("%f",&New_StudentData.GPA);
		break;
	case 5:
		DPRINTF("Enter The New Courses :\n");
		for(i = 0 ;i <5 ; i++)
		{
			DPRINTF("Course %d ID :",i+1);
			gets(temp);
			New_StudentData.CourseIDs[i]=atoi(temp);
		}
		break;
	default:
		DPRINTF("[ERROR] Wrong Choice\n");
		break;
	}


	//Updating the Database
	SMD_error =SMD_UpdateStudent (Local_u32tempRollNumber,Local_u32UserChoice,&New_StudentData);
	switch(SMD_error)
	{
	case SMD_NO_ERROR:
		DPRINTF("[INFO] Update Successfully \n");
		break;
	case SMD_DATABASE_ERROR:
		DPRINTF("[ERROR] Internal Database Error \n");
		break;
	case SMD_WRONG_ROLL_NUMBER:
		DPRINTF("[ERROR] Roll Number Not Found \n");
		break;
	default:
		break;
	}
}





/*==========================================================================================
 * @Fn						-	SMS_voidShowAll
 * @brief					-	This Function will print All Students with their Information to the User
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function will Print All Student Data
 *								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidShowAll(void )
{
	SMD_Error_t SMD_error ;

	SMD_error = SMD_voidShowAll();
	switch(SMD_error)
	{
	case SMD_STUDENT_DATABASE_EMPTY:
		DPRINTF("[ERROR] The Database is EMPTY , Try to Enter Data\n");
		break;
	case SMD_DATABASE_ERROR:
		DPRINTF("[ERROR] The Database NOT READY\n");
		break;
	case SMD_NO_ERROR:
		DPRINTF("[INFO] Student Details is Printed Successfully\n");
		break;
	default:
		break;

	}
}



