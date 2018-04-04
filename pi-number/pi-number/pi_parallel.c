
// #include "stdafx.h"
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <stdio.h>

#define NUM_THREADS 4

int main() {

	static long num_steps = 100000;
	int i = 0;

	// This probably raises the problem of false sharing at the end of the day

	// Change the sum to a variable
	// double sum[NUM_THREADS];
	double pi;
	double step_width = 1.0 / (double)num_steps;
	int ACTUAL_NUM_THREADS;

	// Request 2 threads
	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	{
		// Beginning of the parallel block

		int ID = omp_get_thread_num();
		int i;
		double x = (double)ID;
		double y;
		double sum;
		int nthrds;

		ACTUAL_NUM_THREADS = omp_get_num_threads();

		// Only for the master thread
		//if(ID == 0) {
			// Get the number of generated threads in actual
			//ACTUAL_NUM_THREADS = omp_get_num_threads();
		//}

		// Split the job among the threads
		for (i = ID; i < num_steps; i += ACTUAL_NUM_THREADS) {
			// Beginning of the for block
			
			// Go to the proper x
			x = i * step_width;

			// Find the proper y corresponding to that x
			y = 4.0 / (1.0 + x * x);
			sum += step_width * y;

			// End of the for block
		}

		// Fix the write conflict by assuming sum as a critical variable
		#pragma omp critical
			pi += sum;

			// End of the parallel block
	}

	printf("The computed pi number is equal to: %lf \n", pi);

	return 0;
}
