/*
 * main.c
 *
 *  Created on: Aug 7, 2022
 *      Author: Ephraim
 */

#include "stdio.h"
/*
Write a program in C to print all the alphabets using a pointer. Go
to the editor
Expected Output :
The Alphabets are :
Expected Output :
A B C D E F G H I J K L M N O P Q
R S T U V W X Y Z

 */
int main ()
{
	int i;
	char alpha='A';
	char * p =&alpha;
	printf("This program to Write C code to print all the alphabets using a pointer\n\n");
	printf("The Alphabets are :  ");
	for(i=0;i<26;i++)
	{
		printf("%c ",*p+i);
	}
	return 0;
}
