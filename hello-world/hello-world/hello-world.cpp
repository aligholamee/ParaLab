// hello-world.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <omp.h>


int main()
{
	omp_set_num_threads(10);
	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		printf("Hello(%d) ", ID);
		printf("World(%d) ", ID);
	}
	getchar();
    return 0;
}

