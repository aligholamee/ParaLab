// hello-world.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <omp.h>


int main()
{
	// Set the number of threads
	// Actually it requests this number -> Maybe not available!
	omp_set_num_threads(10000);
	#pragma omp parallel
	{
		// Get the thread number
		// 10 Threads will be running the whole block simultaneously
		int ID = omp_get_thread_num();
		printf("Hello(%d) ", ID);
		printf("World(%d) ", ID);
	}
	getchar();
    return 0;
}

