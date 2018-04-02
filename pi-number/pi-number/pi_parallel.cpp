
// #include "stdafx.h"
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <stdio.h>

int main() {
	
	int num_steps = 50000;
	int i = 0;
	const int num_threads = 5;

	double sum[num_threads];
	double pi = 0.;
	double x = 0.0, y = 0.0;
	double step_width = 1.0 / (double)num_steps;

	// Request 5 threads
	omp_set_num_threads(num_threads);

	#pragma omp parallel
	{	
		int ID = omp_get_thread_num();
		int i = 0;

		#pragma omp critical
		{
			printf("my thread id: %d \n", ID);
		}

		for (i = ID, sum[ID] = 0.0; i < num_steps; i += ID + 1) {
			x += num_threads * step_width;
			y = 4.0 / (1.0 + pow(x, 2.0));
			sum[ID] += step_width * y;
		}
	}

	// Combine the computed results of each thread
	for (i = 0; i < num_threads; i++) {
	    pi += sum[i];
		double temp = sum[i];
		printf("sum[%d] = %lf\n", i, temp);
	}

	// Display the results
	printf("The computed pi number is equal to: %lf", pi);
	// getchar();

	return 0;
}