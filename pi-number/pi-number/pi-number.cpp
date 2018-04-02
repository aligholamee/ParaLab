
#include "stdafx.h"
#include <math.h>


int main()
{
	double sum = 0.0;
	double x = 0, y = 0;
	int num_steps = 50000;
	double step_width = 1.0 / (double)num_steps;
	int i = 0;

	for (i = 0; i < num_steps; i++) {
		x += step_width;
		y = 4.0 / (1.0 + pow(x, 2.0));
		sum += step_width * y;
	}


	printf("The computer pi number is: %lf", sum);
	getchar();
    return 0;
}

