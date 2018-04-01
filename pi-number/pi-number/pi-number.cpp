// pi-number.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>


int main()
{
	double sum = 0.0;
	double x = 0, y = 0;
	int num_steps = 10000;
	int i = 0;

	for (i = 0; i < num_steps; i++)
		x = 1.0 / num_steps;
		y = 4.0 / (1.0 + pow(x, 2.0));
		sum += x * y;

	printf("The computer pi number is: %lf", sum);
	getchar();
    return 0;
}

