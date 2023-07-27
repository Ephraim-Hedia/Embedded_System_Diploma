/*
 * main.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Ephraim
 */

#include "stdio.h"
#include "string.h"



/*
 * HomeWork5
 * EX1:C Program to Store Information (Name ,roll,and Marks) of a Student
 * Using Structure
 *
 * in this program , a structure (student) is created which contains name,roll and marks
 * as its data member . Then, a structure variable is created .
 * Then ,data(name,roll and marks) is taken from user and stored in data members
 * of structure variable . Finally , the data entered by the user is displayed
 *
 * OUTPUT :
 *
 * Enter information of Students :
 *
 * Enter name :Adele
 * Enter Roll Number :21
 * Enter marks :334.5
 *
 *
 * Displaying Information :
 * name : Adele
 * Roll :21
 * Marks :334.50
 *
 *
 * */







struct Sstudent
{
	char 	m_Name[50];
	int 	m_Roll_Number;
	float 	m_Mark;
};

struct Sstudent ReadData(void)
{
	struct Sstudent students ;
	//Enter Name
	printf("Enter Name :");
	fflush(stdin);fflush(stdout);
	scanf("%s",students.m_Name);
	//Enter Roll Number
	printf("Enter Roll Number :");
	fflush(stdin);fflush(stdout);
	scanf("%d",&students.m_Roll_Number);
	//Enter Marks
	printf("Enter Marks :");
	fflush(stdin);fflush(stdout);
	scanf("%f",&students.m_Mark);

	return students;

}
void PrintData(struct Sstudent student)
{
	printf("\nDisplaying Information :\n");
	printf("Name :%s\nRoll :%d\nMarks :%f\n",student.m_Name,student.m_Roll_Number,student.m_Mark);
}

int main ()
{
	struct Sstudent Student;
	Student=  ReadData();
	PrintData(Student);

	return 0;
}
