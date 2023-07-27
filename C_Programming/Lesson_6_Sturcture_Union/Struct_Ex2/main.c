/*
 * main.c
 *
 *  Created on: Jul 29, 2022
 *      Author: Ephraim
 */
#include "stdio.h"
#include "string.h"


/*
 * EX2: C Program to Add Two Distances (in inch-feet) System Using
 * Structure
 *
 *
 * OUTUPT :
 *
 * Enter information for 1st distance
 * Enter feet :12
 * Enter inch :3.45
 *
 * Enter information for 2nd distance
 * Enter feet :12
 * Enter inch :9.2
 *
 *
 * Sum of Distances :25'-0.6"
 *
 *
 *
 *
 * */





struct Sdistance {
	float inch;
	float feet;
};

struct Sdistance readData(char arr[20])
{
	struct Sdistance distances;
	printf("Enter Information for %s\n",arr);
	printf("Enter Feet :");
	fflush(stdin);fflush(stdout);
	scanf("%f",&distances.feet);

	printf("Enter Inch :");
	fflush(stdin);fflush(stdout);
	scanf("%f",&distances.inch);
	return distances;
}

void Sum(struct Sdistance d1,struct Sdistance d2)
{
	struct Sdistance sum;
	sum.feet=d1.feet+d2.feet;
	sum.inch=d1.inch+d2.inch;

	if(sum.inch>=12)
	{
	sum.feet++;
	sum.inch -= 12;}
	printf("Sum of Distance :%.1f \'%.1f\' ",sum.feet,sum.inch);

}
int main ()
{
	struct Sdistance distance1,distance2;
	distance1=readData("1st Distance");
	distance2=readData("2nd Distance");

	Sum(distance1,distance2);

	return 0;
}
