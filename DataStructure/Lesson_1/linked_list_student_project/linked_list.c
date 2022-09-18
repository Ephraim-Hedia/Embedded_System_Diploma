/*
 * linked_list.c
 *
 *  Created on: Sep 17, 2022
 *      Author: ff
 */

#include "linked_list.h"



void AddStudent()
{
	char temp_text[50];
	struct SStudent* pNewStudent ;
	struct SStudent* pLastStudent ;
	//check list is empty ==yes
	if(gpFirstStudent == NULL)
	{
		//Create new First Record
		pNewStudent=(struct SStudent*) malloc (sizeof(struct SStudent));
		//assign it to gpfirst
		gpFirstStudent=pNewStudent;
	}else //list Contains Records
	{
		//Navigate Until reach to the Last Record
		pLastStudent=gpFirstStudent;
		while (pLastStudent->PNextStudent)
			pLastStudent=pLastStudent->PNextStudent;
		//Create New Record
		pNewStudent=(struct SStudent*) malloc(sizeof(struct SStudent));
		pLastStudent->PNextStudent=pNewStudent;
	}
	//fill new Record
	DPRINTF("\n Enter The ID :");
	gets(temp_text);
	pNewStudent->student.ID=atoi(temp_text);

	DPRINTF("\n Enter Student Full Name :");
	gets(pNewStudent->student.name);

	DPRINTF("\n Enter Student Height :");
	gets(temp_text);
	pNewStudent->student.height=atoi(temp_text);

	//Set The Next Pointer (New_Student) NULL
	pNewStudent->PNextStudent=NULL;

}

int delete_student ()
{
	char temp_text[40];
	unsigned int selected_id;
	//get the The Selected id
	DPRINTF("\n Enter The Student id to Be Deleted :");
	gets(temp_text);
	selected_id=atoi(temp_text);

	//List is not Empty
	if (gpFirstStudent)
	{
		struct SStudent *pSelectedStudent=gpFirstStudent;
		struct SStudent *pPreviousStudent=NULL;

		//loop on all Records
		while(pSelectedStudent)
		{
			//Compare each Node with The Selected ID
			if(pSelectedStudent->student.ID ==selected_id)
			{
				if(pPreviousStudent)//The first is not The Selected
				{
					pPreviousStudent->PNextStudent=pSelectedStudent->PNextStudent;
				}else{ //1st Student == ID
					gpFirstStudent=pSelectedStudent->PNextStudent;
				}
				free(pSelectedStudent);
				return 1;
			}
			pPreviousStudent=pSelectedStudent;
			pSelectedStudent=pSelectedStudent->PNextStudent;
		}
	}
	DPRINTF("Cann't Find Student ID\n");
	return 0;
}

int view_node()
{
	unsigned int SelectedIndex,count=0;
	char temp_text[50];
	DPRINTF("\nEnter Node Index :");
	gets(temp_text);
	SelectedIndex=atoi(temp_text);

	//To Check if The List is Empty of NOt
	if(gpFirstStudent)
	{
		struct SStudent *pSelectedStudent=gpFirstStudent;
		while(pSelectedStudent)
		{
			if (count==SelectedIndex)
			{
				DPRINTF("\nThe Information of Student with has Index %d :",count);
				DPRINTF("\nStudent ID : %d",pSelectedStudent->student.ID);
				DPRINTF("\nStudent Name : %s",pSelectedStudent->student.name);
				DPRINTF("\nStudent Height : %f",pSelectedStudent->student.height);
				return 1;
			}
			pSelectedStudent=pSelectedStudent->PNextStudent;
			count ++;
		}
		DPRINTF("The Index not Exist \n");
	}
	else
	{
		DPRINTF("Empty List ");
		return 0;
	}
	return 0;

}

void ReverseList()
{
	struct SStudent *pPreviousStudent=NULL;
	struct SStudent *pCurrentStudent=gpFirstStudent;
	struct SStudent *pNextStudent=NULL;

	while (pCurrentStudent)
	{
		pNextStudent=pCurrentStudent->PNextStudent;
		pCurrentStudent->PNextStudent=pPreviousStudent;
		pPreviousStudent=pCurrentStudent;
		pCurrentStudent=pNextStudent;
	}
	gpFirstStudent=pPreviousStudent;

}




void lengthOfLinkedList()
{
	unsigned int count =0;
	if(gpFirstStudent)
	{
		struct SStudent *pSelectedStudent=gpFirstStudent;
		while(pSelectedStudent)
		{
			pSelectedStudent=pSelectedStudent->PNextStudent;
			count ++;
		}
		DPRINTF("\nThe Length of Linked List = %d",count);

	}
	else
	{
		DPRINTF("\nThe Length of Linked List = %d ",count);

	}

}

int Recursion_lengthOfLinkedList(struct SStudent *pSelectedStudent)
{
	if(pSelectedStudent)
	{
		pSelectedStudent=pSelectedStudent->PNextStudent;
		return (1+Recursion_lengthOfLinkedList(pSelectedStudent));
	}
	else
		return 0;

}

void view_students()
{
	struct SStudent* pCurrentStudent =gpFirstStudent;
	int count =0;
	if(pCurrentStudent==NULL)
	{
		DPRINTF("\n Empty List \n");
	}
	else
	{
		while(pCurrentStudent)
		{
			DPRINTF("\n Record Number %d",count+1);
			DPRINTF("\n\t ID: %d",pCurrentStudent->student.ID);
			DPRINTF("\n\t Name: %s",pCurrentStudent->student.name);
			DPRINTF("\n\t Height: %f",pCurrentStudent->student.height);
			pCurrentStudent=pCurrentStudent->PNextStudent;
			count++;
		}
	}
}


void DeleteAll()
{
	struct SStudent* pCurrentStudent =gpFirstStudent;
	if(pCurrentStudent==NULL)
	{
		DPRINTF("\n Empty List \n");
	}
	else
	{
		while(pCurrentStudent)
		{
			struct SStudent* pTempStudent =pCurrentStudent;
			pCurrentStudent=pCurrentStudent->PNextStudent;
			free(pTempStudent);
		}
		gpFirstStudent=NULL;
	}
}
void middleList()
{
	unsigned int length ,middle;
	struct SStudent* pCurrentStudent =gpFirstStudent;
	if(pCurrentStudent==NULL)
	{
		DPRINTF("\n Empty List \n");
	}
	length =Recursion_lengthOfLinkedList(pCurrentStudent);
	middle =(length /2);

	DPRINTF("\n The middle =%d",middle);

}


int viewNodeFromEnd()
{

	unsigned int NodeNumberFromEnd,length=0,NodeNumberFrombegin=0,count=0;

	char temp_text[50];
	DPRINTF("\nEnter Node Number :");
	gets(temp_text);
	NodeNumberFromEnd=atoi(temp_text);

	length =Recursion_lengthOfLinkedList(gpFirstStudent);

	NodeNumberFrombegin=length-NodeNumberFromEnd-1;



	//To Check if The List is Empty of NOt
	if(gpFirstStudent)
	{
		struct SStudent *pSelectedStudent=gpFirstStudent;
		while(pSelectedStudent)
		{
			if (count==NodeNumberFrombegin)
			{
				DPRINTF("\nThe Information of Student with has Index %d :",count);
				DPRINTF("\nStudent ID : %d",pSelectedStudent->student.ID);
				DPRINTF("\nStudent Name : %s",pSelectedStudent->student.name);
				DPRINTF("\nStudent Height : %f",pSelectedStudent->student.height);
				return 1;
			}
			pSelectedStudent=pSelectedStudent->PNextStudent;
			count ++;
		}
		DPRINTF("The Index not Exist \n");
	}
	else
	{
		DPRINTF("Empty List ");
		return 0;
	}
}
