/*
 * linked_list.h
 *
 *  Created on: Sep 17, 2022
 *      Author: ff
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

#define DPRINTF(...)	{fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}
//effective data
struct Sdata
{
	int ID;
	char name[40];
	float height ;

};

//linked list node
struct SStudent
{
	struct Sdata student;
	struct SStudent* PNextStudent ;
};

struct SStudent* gpFirstStudent;




void AddStudent();
int delete_student ();
int view_node();
void ReverseList();
void lengthOfLinkedList();
int Recursion_lengthOfLinkedList(struct SStudent *pSelectedStudent);
void view_students();
void DeleteAll();
void middleList();
int viewNodeFromEnd();

#endif /* LINKED_LIST_H_ */
