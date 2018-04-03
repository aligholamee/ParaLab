
// #include "stdafx.h"
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <stdio.h>

#define NUM_THREADS 4

int main() {

	int num_steps = 50000;
	int i = 0;

	// This probably raises the problem of false sharing at the end of the day
	double sum[NUM_THREADS];
	double pi = 0.0;
	double step_width = 1.0 / (double)num_steps;
	int ACTUAL_NUM_THREADS = 0;

	// Request 5 threads
	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		int i = 0;
		double x = 0.0;
		double y = 0.0;


		#pragma omp critical
		{
			printf("my thread id: %d \n", ID);
		}

		// Only for the master thread
		if(ID == 0) {
			// Get the number of generated threads in actual
			ACTUAL_NUM_THREADS = omp_get_num_threads();
		}

		// Split the job among the threads
		for (i = ID, sum[ID] = 0.0; i < num_steps; i += ACTUAL_NUM_THREADS) {
			x += (i);
			y = 4.0 / (1.0 + x * x);
			sum[ID] += step_width * y;
		}
	}

	// Combine the computed results of each thread
	for (i = 0; i < ACTUAL_NUM_THREADS; i++) {
	    pi += sum[i];
		double temp = sum[i];
		printf("sum[%d] = %lf\n", i, temp);
	}

	// Display the results
	printf("The computed pi number is equal to: %lf\n", pi);
	// getchar();

	return 0;
}
