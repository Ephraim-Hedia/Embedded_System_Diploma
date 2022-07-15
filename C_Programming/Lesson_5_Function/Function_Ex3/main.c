/*
 * main.c
 *
 *  Created on: Jul 15, 2022
 *      Author: Ephraim
 */

#include "stdio.h"
#include "string.h"
void reverse(void){
    char c;

    // Asking for Input
    scanf("%c", &c);
    if (c != '\n') // If the variable is any character other than \n (newline)
    {
        reverse();
        printf("%c", c);
    }
}
//This program prints "Please enter a sentence: " in screen and then takes input from the user.
//reverse() function called and function stores the first letter entered by user and stores in variable c.
//If that variable is other than '\n' [enter character] then, again reverse() function is called.
//Then, the second character is stored in variable c of second reverse function.
//This process goes on until the user enters '\n'.


void main (void)
{
	printf("This C program takes a input from user and reverses that sentence using recursion.\n\n");
	printf("Enter a Sentence :");
	fflush(stdin);fflush(stdout);
	reverse();

}
