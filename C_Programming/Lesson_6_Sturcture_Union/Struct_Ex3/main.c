/*
 * main.c
 *
 *  Created on: Jul 30, 2022
 *      Author: Ephraim
 */

#include "stdio.h"
#include "string.h"




/*
 *	EX3:C Program to Add Two Complex Number by Passing Structure
 *	to a Function
 *
 *	OUTPUT :
 *
 *	For 1st complex Number
 *	Enter real and imaginary respectively :2.3
 *	4.5
 *
 *	For 2st complex Number
 *	Enter real and imaginary respectively :3.4
 *	5
 *
 *	Sum = 5.7+9.5i
 *
 */



struct Scomplex{
	float real ;
	float img ;
};

struct Scomplex readData(char arr[20])
{
	struct Scomplex number;
	printf("for %s \nEnter Real and Imaginary respectively :",arr);
	fflush(stdin);fflush(stdout);
	scanf("%f %f",&number.real,&number.img);
	return number;

}
void Sum_Complex(struct Scomplex x,struct Scomplex y)
{
	struct Scomplex sum;
	sum.real=x.real+y.real;
	sum.img=x.img+y.img;

	printf("Sum = %.1f + %.1fi",sum.real,sum.img);
}
int main ()
{
	struct Scomplex N1,N2;
	N1=readData("1st Complex Number");
	N2=readData("2nd Complex Number");
	Sum_Complex(N1,N2);
	return 0;
}
