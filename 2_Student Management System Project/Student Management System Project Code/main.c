/*
 * main.c
 *
 *  Created on: Sep 8, 2022
 *      Author: Guirguis
 */

#include "linked_list.h"

int main()
{
	char temp_text[40];
	int count;
	while(1)
	{
		DPRINTF("\n ==================");
		DPRINTF("\n\t Choose on of the Following Option :\n");
		DPRINTF("\n 1:AddStudent ");
		DPRINTF("\n 2:DeleteStudent ");
		DPRINTF("\n 3:viewStudent ");
		DPRINTF("\n 4: DeleteAll");
		DPRINTF("\n 5: viewNode ");
		DPRINTF("\n 6: lengthOfLinkedList ");
		DPRINTF("\n 7: Recursion_lengthOfLinkedList ");
		DPRINTF("\n 8: ReverseList ");
		DPRINTF("\n 9: middleList ");
		DPRINTF("\n 10: viewNodeFromEnd ");
		DPRINTF("\n Enter Option Number :");
		gets(temp_text);
		DPRINTF("\n ===================");
		switch(atoi(temp_text))
		{
		case 1:
			AddStudent();
			break;
		case 2:
			delete_student();
			break;
		case 3:
			view_students();
			break;
		case 4:
			DeleteAll();
			break;
		case 5:
			view_node();
			break;
		case 6:
			lengthOfLinkedList();
			break;
		case 7:
			count=Recursion_lengthOfLinkedList(gpFirstStudent);
			DPRINTF("\nThe Length of Linked List = %d",count);
			break;
		case 8:
			ReverseList();
			break;
		case 9:
			middleList();
			break;
		case 10:
			viewNodeFromEnd();
			break;
		default:
			DPRINTF("\n Wrong Option");
			break;
		}
	}
	return 0;

}

