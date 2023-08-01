/*
 * Student_Mangement_System.h
 *
 *  Created on: Jul 21, 2023
 *      Author: Ephraim
 */

#ifndef STUDENT_MANGEMENT_SYSTEM_H_
#define STUDENT_MANGEMENT_SYSTEM_H_

#define DPRINTF(...)	{fflush(stdout);\
						fflush(stdin);\
						printf(__VA_ARGS__);\
						fflush(stdout);\
						fflush(stdin);}



typedef struct
{
	char FirstName[20];
	char LastName[20];
	int RollNumber;
	float GPA;
	int CourseIDs[5];
}sStudentDetail_t;


/*==========================================================================================
 * @Fn						- 	SMS_voidInit
 * @brief					- 	Initialize the Database of the System
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function Prints if the Function Successfully
 * 								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidInit(void);





/*==========================================================================================
 * @Fn						-	SMS_voidAddStudentUsingTextFile
 * @brief					-	Adding Student Data To the Database Using Text File (Must Every Student Have A unique Roll Number)
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function Prints if the Function Successfully
 * 								OR if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidAddStudentUsingTextFile(void);





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
void SMS_voidAddStudentManually(void);




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
void SMS_voidFindStudentUsingRollNumber(void);





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
void SMS_voidFindStudentUsingFirstName(void);





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
void SMS_voidFindStudentUsingCourseID(void);





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
void SMS_voidFindTotalStudentsNumber(void);






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
void SMS_voidDeleteStudent(void);





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
void SMS_voidUpdateStudent(void);




/*==========================================================================================
 * @Fn						-	SMS_voidShowAll
 * @brief					-	This Function will print All Students with their Information to the User
 * @param[in]				-	NONE
 * @retval					-	NONE
 * Note						-	The Function will Print All Student Data
 *								and if The Function has an Error ,it will print the Error
 *==========================================================================================
 */
void SMS_voidShowAll(void);









#endif /* STUDENT_MANGEMENT_SYSTEM_H_ */
