/*
 * Student_Mangement_Database.c
 *
 *  Created on: Jul 22, 2023
 *      Author: Ephraim
 */

#include "stdio.h"
#include "Student_Mangement_System.h"
#include "Student_Mangement_Database.h"
#include "Student_Mangement_Queue.h"


/*
 * ==========================================================================================
 * 									Generic Macros
 * ==========================================================================================
 */
#define DATABASE_SIZE		50
#define NUMBER_OF_COURSES	5


/*
 * ==========================================================================================
 * 									Generic Variables
 * ==========================================================================================
 */
sStudentDetail_t Global_StudentDatabase[DATABASE_SIZE];
FIFO_Buf_t Global_StudentFIFO;




/*
 * ==========================================================================================
 * 									Generic Functions
 * ==========================================================================================
 */

static int SMD_checkOfRollNumber (unsigned int Copy_u32RollNumber)
{
	int i ;
	char Local_u8Flag =0;
	FIFO_Buf_t Local_tempFIFO;
	Local_tempFIFO =Global_StudentFIFO;

	for (i=0 ; i< Global_StudentFIFO.count;i++)
	{
		if(Local_tempFIFO.tail->RollNumber==Copy_u32RollNumber)
		{
			Local_u8Flag=1;
			break;
		}
		else
		{
			Local_tempFIFO.tail++;
		}
	}
	if(Local_u8Flag == 1)
		return SMD_REPEATED_ROLL_NUMBER;

	return SMD_NO_ERROR;
}


/*
 * ==========================================================================================
 * 								APIs Function Definitions
 * ==========================================================================================
 */

/*==========================================================================================
 * @Fn						- 	SMD_InitDatabase
 * @brief					- 	Initialize the Database of the System
 * @param[in]				-	NONE
 * @retval					-	SMD_Error_t
 * Note						-	This Function Links the Global_StudentDatabase array with Global_StudentFIFO
 * 								and Check After That if the Linking Done Correctly or NO
 *==========================================================================================
 */
SMD_Error_t SMD_InitDatabase(void)
{
	FIFO_Buf_Status FIFO_error;
	FIFO_error = FIFO_init(&Global_StudentFIFO,Global_StudentDatabase);
	switch (FIFO_error)
	{
	case FIFO_no_error:
		FIFO_error=FIFO_no_error;
		break;
	case FIFO_null:
		FIFO_error=FIFO_null;
		break;
	default :
		break;
	}
	return FIFO_error;
}

/*==========================================================================================
 * @Fn						- 	SMD_AddStudentFromTextFile
 * @brief					- 	Input the Data in the Text File into the database of the system
 * @param[in]				-	Student							-->Return To the User The data of Students
 * @param[in]				-	Copy_u32NumberOfRecords			-->Return To the User the number of Student we recorded
 * @retval					-	SMD_Error_t
 * Note						-	You Must Write THe text File with 9 INPUT
 * 								and Separated each input by comma
 * 							-	File Name Must be Student_Database.txt
 * 							-	No Check Syntax Feature With The File , So be Careful with Your Data
 *==========================================================================================
 */

SMD_Error_t SMD_AddStudentFromTextFile(sStudentDetail_t* Student ,unsigned int *Copy_u32NumberOfRecords)
{

	unsigned int Local_u32NumberOfReading = 0 ;
	FILE *file ;


	*Copy_u32NumberOfRecords = 0 ;
	file =fopen("Student_Database.txt","r");
	if(file == NULL)
	{
		return SMD_FILE_NOT_OPEN;
	}

	do
	{
		Local_u32NumberOfReading =fscanf(file,"%20[^,],%20[^,],%d,%f,%d,%d,%d,%d,%d\n",
				Student->FirstName,
				Student->LastName,
				&(Student->RollNumber),
				&(Student->GPA),
				&(Student->CourseIDs[0]),
				&(Student->CourseIDs[1]),
				&(Student->CourseIDs[2]),
				&(Student->CourseIDs[3]),
				&(Student->CourseIDs[4]));

		if(Local_u32NumberOfReading == 9)
		{
			(*Copy_u32NumberOfRecords)++;
			Student++;
		}
		if(Local_u32NumberOfReading != 9 && !feof(file))
		{
			return SMD_FILE_WRONG_FORMAT;
		}

		if(ferror(file))
		{
			return SMD_FILE_READING_ERROR;
		}

	}while(!feof(file));
	fclose(file);

	return SMD_NO_ERROR;
}


/*==========================================================================================
 * @Fn						- 	SMD_AddStudent
 * @brief					- 	Add Student in the database with Checking Mechansim about
 * 								if the database has internal ERROR
 * 								or if the database is full , Or if you Enter Repeated Roll Number
 * @param[in]				-	Student	--> The data of the Student
 * @retval					-	SMD_Error_t
 * Note						-	You Must Choose not repeated Roll Number During Enter Your Data
 *
 *==========================================================================================
 */
SMD_Error_t SMD_AddStudent(sStudentDetail_t* Student)
{
	FIFO_Buf_Status FIFO_error;
	SMD_Error_t SMD_error;


	//Check First About the roll Number
	SMD_error =SMD_checkOfRollNumber(Student->RollNumber);

	if(SMD_error == SMD_REPEATED_ROLL_NUMBER)
		{return SMD_REPEATED_ROLL_NUMBER;}


	FIFO_error = FIFO_enqueue(&Global_StudentFIFO , Student);
	switch (FIFO_error)
	{
	case FIFO_no_error:
		SMD_error=SMD_NO_ERROR;
		break;
	case FIFO_null:
		SMD_error = SMD_DATABASE_ERROR;
		break;
	case FIFO_full:
		SMD_error=SMD_STUDENT_DATABASE_FULL;
		break;
	default:
		break;
	}
	return SMD_error;
}

/*==========================================================================================
 * @Fn						- 	SMD_FindStudentUsingRollNumber
 * @brief					- 	Searching About Student data Using Roll Number
 * @param[in]				-	Student						--> Return the data of the Student to the Upper Layer
 * @param[in]				-   Copy_u32RollNumber			--> The Roll Number You are Search For
 * @retval					-	SMD_Error_t
 * Note						-	The Roll number is Unique So the OUTPUT will be One Student Only
 *
 *==========================================================================================
 */

SMD_Error_t SMD_FindStudentUsingRollNumber	(int 	Copy_u32RollNumber		,sStudentDetail_t* Student )
{
	int i ;
	char Local_u8Flag =0;
	FIFO_Buf_t Local_tempFIFO;
	Local_tempFIFO =Global_StudentFIFO;


	for (i=0 ; i< Global_StudentFIFO.count;i++)
	{
		if(Local_tempFIFO.tail->RollNumber==Copy_u32RollNumber)
		{
			*Student=*(Local_tempFIFO.tail);
			Local_u8Flag=1;
			break;
		}
		else
		{
			Local_tempFIFO.tail++;
		}
	}
	if(Local_u8Flag == 0)
		return SMD_WRONG_ROLL_NUMBER;

	return SMD_NO_ERROR;
}


/*==========================================================================================
 * @Fn						- 	SMD_FindStudentUsingFirstName
 * @brief					- 	Searching About Student data Using First
 * @param[in]				-   Copy_u8FirstName			--> The Roll Number You are Search For
 * 							-	Student						--> Return the data of the Student to the Upper Layer
 * 							-	Copy_u32NumberOfStudent		--> Return Number of Student we Find with the first name to the Upper Layer
 * @retval					-	SMD_Error_t
 * Note						-	The First Name Not Unique So the OUTPUT may be more than one Student
 *
 *==========================================================================================
 */
SMD_Error_t SMD_FindStudentUsingFirstName	(char* 	Copy_u8FirstName		,sStudentDetail_t* Student ,int * Copy_u32NumberOfStudent)
{
	int i ;
	char Local_u8Flag =0;
	FIFO_Buf_t Local_tempFIFO;
	Local_tempFIFO =Global_StudentFIFO;
	*Copy_u32NumberOfStudent = 0;

	for (i=0 ; i< Global_StudentFIFO.count;i++)
	{
		if(strcmp(Local_tempFIFO.tail->FirstName,Copy_u8FirstName)==0)
		{
			*Student=*(Local_tempFIFO.tail);
			Local_u8Flag=1;
			Student ++;
			(*Copy_u32NumberOfStudent)++;

		}
		Local_tempFIFO.tail++;
	}
	if(Local_u8Flag == 0)
			return SMD_WRONG_FirstName;
	return SMD_NO_ERROR;
}



/*==========================================================================================
 * @Fn						- 	SMD_FindStudentUsingCourseID
 * @brief					- 	Searching About Students data CourseID
 * @param[in]				-   Copy_u32CourseID			--> The Course ID Number You are Search For
 * 							-	Student						--> Return the data of the Student to the Upper Layer
 * 							-	Copy_u32NumberOfStudent		--> Return Number of Student we Find with the first name to the Upper Layer
 * @retval					-	SMD_Error_t
 * Note						-	The Course ID Not Unique So the OUTPUT may be more than one Student
 *
 *==========================================================================================
 */
SMD_Error_t SMD_FindStudentUsingCourseID	(int 	Copy_u32CourseID    	,sStudentDetail_t* Student ,int * Copy_u32NumberOfStudent)
{
	int i ,j;
	FIFO_Buf_t Local_tempFIFO;
	Local_tempFIFO =Global_StudentFIFO;
	char Local_u8Flag =0;
	* Copy_u32NumberOfStudent = 0 ;

	if(!Local_tempFIFO.head || !Local_tempFIFO.base || !Local_tempFIFO.tail)
		return SMD_DATABASE_ERROR;

	//Looping On all Students in the Database
	for (i=0 ; i< Global_StudentFIFO.count;i++)
	{
		//Looping on All Courses The Student Selected
		for(j=0 ; j<NUMBER_OF_COURSES;j++)
		{
			if(Local_tempFIFO.tail->CourseIDs[j]==Copy_u32CourseID)
			{
				*Student=*(Local_tempFIFO.tail);
				Local_u8Flag=1;
				Student ++;
				(*Copy_u32NumberOfStudent)++;
				break;
			}
		}
		Local_tempFIFO.tail ++;
	}
	if(Local_u8Flag == 0)
				return SMD_COURSE_ID_NOT_FOUND;

	return SMD_NO_ERROR;
}



/*==========================================================================================
 * @Fn						- 	SMD_FindTotalStudentsNumber
 * @brief					- 	Searching About Total Student Number in the database
 * @param[in]				-   Copy_u32TotalStudentNumber	--> Return the Total Number of Students to the Upper Layer
 * @retval					-	SMD_Error_t
 * Note						-
 *
 *==========================================================================================
 */
SMD_Error_t	SMD_FindTotalStudentsNumber(int * Copy_u32TotalStudentNumber)
{
	//Check if The FIFO is Empty
	if (Global_StudentFIFO.count == 0 )
		return SMD_STUDENT_DATABASE_EMPTY;

	*Copy_u32TotalStudentNumber =Global_StudentFIFO.count;
	return SMD_NO_ERROR;
}


/*==========================================================================================
 * @Fn						- 	SMD_DeleteStudent
 * @brief					- 	Deleting the Student Data from the Database Using the Roll Number
 * @param[in]				-   Copy_u32RollNumber	--> The Roll Number we will Use to Delete the Student from the Database
 * @retval					-	SMD_Error_t
 * Note						-
 *
 *==========================================================================================
 */
SMD_Error_t SMD_DeleteStudent (int 	Copy_u32RollNumber)
{
	int i ;
	char Local_u8Flag =0;
	FIFO_Buf_t Local_tempFIFO;
	Local_tempFIFO =Global_StudentFIFO;
	sStudentDetail_t TempStudent ;
	sStudentDetail_t TempStudentbuff[50] ;
	unsigned char Local_u8Index = 0;

	//Check if the Database Has an Error
	if(!Local_tempFIFO.head || !Local_tempFIFO.base || !Local_tempFIFO.tail)
		return SMD_DATABASE_ERROR;

	//Check if the Database is Empty
	if(Local_tempFIFO.count==0)
		return SMD_STUDENT_DATABASE_EMPTY;

	//Check if the Roll Number is Exist
	for (i=0 ; i< Global_StudentFIFO.count;i++)
	{
		if(Local_tempFIFO.tail->RollNumber==Copy_u32RollNumber)
		{
			Local_u8Flag=1;
			break;
		}
		else
		{
			Local_tempFIFO.tail++;
			Local_u8Index++;
		}
	}





	if(Local_u8Flag == 0) //If the Roll Number Not Found
			return SMD_WRONG_ROLL_NUMBER;
	else //If the Roll Number is Exist
	{
		if(Local_tempFIFO.count==1)
		{
			//So there is One Element in the DataBase in the Begining and Tail Pointer points on it
			//So We will Use dequeue Function Directly
			FIFO_dequeue(&Global_StudentFIFO,&TempStudent);
		}
		else if (Local_tempFIFO.count > 1)
		{
			//Put Address of Struct of Student
			Local_tempFIFO =Global_StudentFIFO;
			for( i = 0 ; i< Local_u8Index ; i++)
			{
				TempStudentbuff[i] =*(Local_tempFIFO.tail);
				Local_tempFIFO.tail++;
			}

			Local_tempFIFO =Global_StudentFIFO;
			for( i = 0 ; i< Local_u8Index ; i++)
			{
				Local_tempFIFO.tail++;
				*Local_tempFIFO.tail =TempStudentbuff[i];
			}
			Global_StudentFIFO.tail++;
			Global_StudentFIFO.count--;
		}
		else
		{
			//Not Exist
		}
	}

	return SMD_NO_ERROR;
}


/*==========================================================================================
 * @Fn						- 	SMD_UpdateStudent
 * @brief					- 	Updating the Student Data from the Database Using the Roll Number
 * @param[in]				-   Copy_u32RollNumber	--> The Roll Number we will Use to Update the Student from the Database
 * 							-	Copy_u32UserChoice	--> You Can Choose Here What you Want to Update Like :FirstName , LastName,RollNumber,...
 * 							-	Copy_NewStudentData	--> You Must Give the Function the NewData You Want to be updated
 * @retval					-	SMD_Error_t
 * Note						-
 *
 *==========================================================================================
 */
SMD_Error_t SMD_UpdateStudent (int Copy_u32RollNumber,int Copy_u32UserChoice, sStudentDetail_t* Copy_NewStudentData)
{

	int i ;
	char Local_u8Flag =0;
	FIFO_Buf_t Local_tempFIFO;
	Local_tempFIFO =Global_StudentFIFO;

	//Find The Element we want to Modify and Make Sure The Roll Number is Exist
	//if the Roll Number Not Exist so The Element Not Exist
	//and we will return to the Wrong roll Number

	for (i=0 ; i< Global_StudentFIFO.count;i++)
	{
		if(Local_tempFIFO.tail->RollNumber==Copy_u32RollNumber)
		{
			Local_u8Flag=1;
			break;
		}
		else
		{
			Local_tempFIFO.tail++;
		}
	}
	if(Local_u8Flag == 0)
		return SMD_WRONG_ROLL_NUMBER;

	//We will Check About the Choice The User Entered
	//and Begin to Change the Data

	switch(Copy_u32UserChoice)
	{
	case 1:
		//Change the First Name with New Data
		strcpy(Local_tempFIFO.tail->FirstName,Copy_NewStudentData->FirstName);
		break;
	case 2:
		//Change the Last Name with New Data
		strcpy(Local_tempFIFO.tail->LastName,Copy_NewStudentData->LastName);
		break;
	case 3:
		//Change the Roll Number with New Data
		Local_tempFIFO.tail->RollNumber=Copy_NewStudentData->RollNumber;
		break;
	case 4:
		Local_tempFIFO.tail->GPA=Copy_NewStudentData->GPA;
		//Change the GPA with New Data
		break;
	case 5:
		for (i=0;i<5;i++)
		{
			Local_tempFIFO.tail->CourseIDs[i]=Copy_NewStudentData->CourseIDs[i];
		}
		//Change the Courses IDs with New Data
		break;
	default :
		break;
	}

	return SMD_NO_ERROR;
}


/*==========================================================================================
 * @Fn						- 	SMD_voidShowAll
 * @brief					- 	Show ALl information in the Database to the User
 * @param[in]				-   NONE
 * @retval					-	SMD_Error_t
 * Note						-
 *
 *==========================================================================================
 */
SMD_Error_t SMD_voidShowAll(void)
{
	sStudentDetail_t * tempStudent;
	int i ,j;
	tempStudent =Global_StudentFIFO.tail;

	//Check if The FIFO is Empty
	if (Global_StudentFIFO.count == 0 )
		return SMD_STUDENT_DATABASE_EMPTY;

	//Print Data if the FIFO NOT Empty
	DPRINTF("\n--------------------------------------\n" );
	for(i = 0 ; i<Global_StudentFIFO.count;i++)
	{
		DPRINTF("Student First Name : %s\n" ,tempStudent->FirstName);
		DPRINTF("Student Last Name : %s\n" ,tempStudent->LastName);
		DPRINTF("Student Roll Number : %d\n" ,tempStudent->RollNumber);
		DPRINTF("Student GPA : %f\n" ,tempStudent->GPA);
		for(j =0 ; j <5 ; j++)
		{
			DPRINTF("The Course ID are %d \n",tempStudent->CourseIDs[j]);
		}
		DPRINTF("--------------------------------------\n" );
		tempStudent++;
	}


	return SMD_NO_ERROR;
}
