/*
 * Student_Mangement_Database.h
 *
 *  Created on: Jul 22, 2023
 *      Author: Ephraim
 */

#ifndef STUDENT_MANGEMENT_DATABASE_H_
#define STUDENT_MANGEMENT_DATABASE_H_

typedef enum
{
	SMD_NO_ERROR,
	SMD_FILE_NOT_OPEN,
	SMD_FILE_WRONG_FORMAT,
	SMD_FILE_READING_ERROR,
	SMD_STUDENT_DATABASE_FULL,
	SMD_DATABASE_ERROR,
	SMD_WRONG_ROLL_NUMBER,
	SMD_REPEATED_ROLL_NUMBER,
	SMD_WRONG_FirstName,
	SMD_COURSE_ID_NOT_FOUND,
	SMD_STUDENT_DATABASE_EMPTY
}SMD_Error_t;


/*==========================================================================================
 * @Fn						- 	SMD_InitDatabase
 * @brief					- 	Initialize the Database of the System
 * @param[in]				-	NONE
 * @retval					-	SMD_Error_t
 * Note						-	This Function Links the Global_StudentDatabase array with Global_StudentFIFO
 * 								and Check After That if the Linking Done Correctly or NO
 *==========================================================================================
 */

SMD_Error_t SMD_InitDatabase(void);


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
SMD_Error_t SMD_AddStudentFromTextFile(sStudentDetail_t* Student ,unsigned int *Copy_u32NumberOfRecords);
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
SMD_Error_t SMD_AddStudent(sStudentDetail_t* Student);




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
SMD_Error_t SMD_FindStudentUsingRollNumber	(int 	Copy_u32RollNumber		,sStudentDetail_t* Student );




/*==========================================================================================
 * @Fn						- 	SMD_FindStudentUsingFirstName
 * @brief					- 	Searching About Student data Using First
 * @param[in]				-   Copy_u8FirstName			--> The Roll Number You are Search For
 * @param[in]				-	Student						--> Return the data of the Student to the Upper Layer
 * @param[in]				-	Copy_u32NumberOfStudent		--> Return Number of Student we Find with the first name to the Upper Layer
 * @retval					-	SMD_Error_t
 * Note						-	The First Name Not Unique So the OUTPUT may be more than one Student
 *
 *==========================================================================================
 */
SMD_Error_t SMD_FindStudentUsingFirstName	(char* 	Copy_u8FirstName		,sStudentDetail_t* Student ,int * Copy_u32NumberOfStudent);






/*==========================================================================================
 * @Fn						- 	SMD_FindStudentUsingCourseID
 * @brief					- 	Searching About Students data CourseID
 * @param[in]				-   Copy_u32CourseID			--> The Course ID Number You are Search For
 * @param[in]				-	Student						--> Return the data of the Student to the Upper Layer
 * @param[in]				-	Copy_u32NumberOfStudent		--> Return Number of Student we Find with the first name to the Upper Layer
 * @retval					-	SMD_Error_t
 * Note						-	The Course ID Not Unique So the OUTPUT may be more than one Student
 *
 *==========================================================================================
 */
SMD_Error_t SMD_FindStudentUsingCourseID	(int 	Copy_u32CourseID    	,sStudentDetail_t* Student ,int * Copy_u32NumberOfStudent);




/*==========================================================================================
 * @Fn						- 	SMD_FindTotalStudentsNumber
 * @brief					- 	Searching About Total Student Number in the database
 * @param[in]				-   Copy_u32TotalStudentNumber	--> Return the Total Number of Students to the Upper Layer
 * @retval					-	SMD_Error_t
 * Note						-
 *
 *==========================================================================================
 */
SMD_Error_t	SMD_FindTotalStudentsNumber(int * Copy_u32TotalStudentNumber);




/*==========================================================================================
 * @Fn						- 	SMD_DeleteStudent
 * @brief					- 	Deleting the Student Data from the Database Using the Roll Number
 * @param[in]				-   Copy_u32RollNumber	--> The Roll Number we will Use to Delete the Student from the Database
 * @retval					-	SMD_Error_t
 * Note						-
 *
 *==========================================================================================
 */
SMD_Error_t SMD_DeleteStudent (int 	Copy_u32RollNumber);





/*==========================================================================================
 * @Fn						- 	SMD_UpdateStudent
 * @brief					- 	Updating the Student Data from the Database Using the Roll Number
 * @param[in]				-   Copy_u32RollNumber	--> The Roll Number we will Use to Update the Student from the Database
 * @param[in]				-	Copy_u32UserChoice	--> You Can Choose Here What you Want to Update Like :FirstName , LastName,RollNumber,...
 * @param[in]				-	Copy_NewStudentData	--> You Must Give the Function the NewData You Want to be updated
 * @retval					-	SMD_Error_t
 * Note						-
 *
 *==========================================================================================
 */
SMD_Error_t SMD_UpdateStudent (int Copy_u32RollNumber,int Copy_u32UserChoice, sStudentDetail_t* Copy_NewStudentData);





/*==========================================================================================
 * @Fn						- 	SMD_voidShowAll
 * @brief					- 	Show ALl information in the Database to the User
 * @param[in]				-   NONE
 * @retval					-	SMD_Error_t
 * Note						-
 *
 *==========================================================================================
 */
SMD_Error_t SMD_voidShowAll(void);

#endif /* STUDENT_MANGEMENT_DATABASE_H_ */
