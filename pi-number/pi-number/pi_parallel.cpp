
#include "stdafx.h"
#include <stdlib.h>
#include <omp.h>

int main() {
	
	int num_steps = 50000;
	int i = 0;
	const int num_threads = 5;

	double sum[num_threads] = { 0 };
	double x = 0.0, y = 0.0;
	double step_width = 1.0 / (double)num_steps;

	// Request 5 threads
	omp_set_num_threads(num_threads);

	#pragma omp parallel 
	{	
		int ID = omp_get_thread_num();
		for (i = 0; i < num_steps; i += ID) {


		}
	}


}