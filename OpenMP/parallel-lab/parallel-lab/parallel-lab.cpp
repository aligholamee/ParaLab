// Example Program
#include "stdafx.h"

// Optimizes code for maximum speed in serial mode

#pragma optimize( "2", on )
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <omp.h>
#include <math.h>

// Adds an additional library so that timeGetTime() can be used
#pragma comment(lib, "winmm.lib")
const long int VERYBIG = 100000;
const int NUM_THREADS = 8;

// ***********************************************************************
int main(void)
{
	int i;
	long int j, k, sum;
	double total;
	DWORD starttime, elapsedtime;
	// -----------------------------------------------------------------------
	// Output a start message
	printf("Parallel Timings for %d iterations\n\n", VERYBIG);
	// repeat experiment several times

	omp_set_num_threads(NUM_THREADS);

	for (i = 0; i<6; i++)
	{
		// get starting time56 x CHAPTER 3 PARALLEL STUDIO XE FOR THE IMPATIENT
		starttime = timeGetTime();
		// reset check sum & running total
		sum = 0;
		total = 0.0;
		// Work Loop, do some work by looping VERYBIG times

		#pragma omp parallel for reduction(+:sum, total) schedule(static, 1000)
		for (j = 0; j<VERYBIG; j++)
		{
			// increment check sum
			sum += 1;
			// Calculate first arithmetic series
			// Fixed private access
			double sumx = 0.0;
			#pragma omp parallel for reduction(+:sumx)
			for (k = 0; k<j; k++) 
				sumx += (double)k;
			// Calculate second arithmetic series
			double sumy = 0.0;
			#pragma omp parallel for reduction(+:sumy)
			for (k = j; k>0; k--)
				sumy += (double)k;
			if (sumx > 0.0)total += 1.0 / sqrt(sumx);
			if (sumy > 0.0)total += 1.0 / sqrt(sumy);
		}
		// get ending time and use it to determine elapsed time
		elapsedtime = timeGetTime() - starttime;
		// report elapsed time
		printf("Time Elapsed % 10d mSecs Total = %lf Check Sum = %ld\n",
			(int)elapsedtime, total, sum);
	}


	// return integer as required by function header
	return 0;
}
// **********************************************************************