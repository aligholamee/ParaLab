
#include <math.h>
#include <omp.h>
#include <stdio.h>

int main()
{
	double sum = 0.0;
	double x = 0.0, y = 0.0;
	int num_steps = 50000;
	double step_width = 1.0 / (double)num_steps;
	int i = 0;
	
	#pragma omp parallel for reduction(+:sum)
	for (i = 0; i < num_steps; i++) {
		x = (i + 0.5) * step_width;
		y = 4.0 / (1.0 + x * x);
		sum += step_width * y;
	}

	printf("The computed pi number is: %lf", sum);
  return 0;
}
