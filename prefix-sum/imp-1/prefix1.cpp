/*
*				In His Exalted Name
*	Title:	Prefix Sum Sequential Code
*	Author: Ahmad Siavashi, Email: siavashi@aut.ac.ir
*	Date:	29/04/2018
*	Parallelization: Ali Gholami
*/

// Let it be.
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define NUM_THREADS 8

void omp_check();
void fill_array(int *a, size_t n);
void prefix_sum(int *a, size_t n);
void print_array(int *a, size_t n);

int main(int argc, char *argv[]) {
	// Check for correct compilation settings
	omp_check();
	// Input N
	size_t n = 0;
	printf("[-] Please enter N: ");
	scanf("%uld\n", &n);
	// Allocate memory for array
	int * a = (int *)malloc(n * sizeof a);

	int NUM_RUN = 1;
	double start_time = 0.0, elapsed_time = 0.0;

	// Fill array with numbers 1..n
	fill_array(a, n);
	// Print array
	print_array(a, n);

	omp_set_num_threads(NUM_THREADS);

	for (int i = 0; i < NUM_RUN; i++) {

		start_time = omp_get_wtime();

		// Compute prefix sum
		prefix_sum(a,  n);

		elapsed_time += omp_get_wtime() - start_time;

	}

	printf("\n[INFO] Computation average time %lf \n",  elapsed_time / NUM_RUN);

	// Print array
	print_array(a, n);
	// Free allocated memory
	free(a);

	system("pause");

	return EXIT_SUCCESS;
}

void prefix_sum(int *a, size_t n) {
	int amount = (int)(n / NUM_THREADS);
	int start[NUM_THREADS];
	int end[NUM_THREADS];
#pragma omp parallel firstprivate(amount)
	{
		int thread_num = omp_get_thread_num();
		start[thread_num] = thread_num * amount;
		end[thread_num] = (thread_num + 1)*amount - 1;
		for (int i = start[thread_num]; i < end[thread_num]; ++i) {
			a[i + 1] += a[i];
		}
	}
	for (int i = 0; i < NUM_THREADS - 1; i++) {
		for (int j = start[i + 1]; j <= end[i + 1]; ++j) {
			a[j] += a[end[i]];
		}
	}
}

void print_array(int *a, size_t n) {
	int i;
	printf("[-] array: ");
	for (i = 0; i < n; ++i) {
		printf("%d, ", a[i]);
	}
	printf("\b\b  \n");
}

void fill_array(int *a, size_t n) {
	int i;
	for (i = 0; i < n; ++i) {
		a[i] = i + 1;
	}
}

void omp_check() {
	printf("------------ Info -------------\n");
#ifdef _DEBUG
	printf("[!] Configuration: Debug.\n");
#pragma message ("Change configuration to Release for a fast execution.")
#else
	printf("[-] Configuration: Release.\n");
#endif // _DEBUG
#ifdef _M_X64
	printf("[-] Platform: x64\n");
#elif _M_IX86 
	printf("[-] Platform: x86\n");
#pragma message ("Change platform to x64 for more memory.")
#endif // _M_IX86 
#ifdef _OPENMP
	printf("[-] OpenMP is on.\n");
	printf("[-] OpenMP version: %d\n", _OPENMP);
#else
	printf("[!] OpenMP is off.\n");
	printf("[#] Enable OpenMP.\n");
#endif // _OPENMP
	printf("[-] Maximum threads: %d\n", omp_get_max_threads());
	printf("[-] Nested Parallelism: %s\n", omp_get_nested() ? "On" : "Off");
#pragma message("Enable nested parallelism if you wish to have parallel region within parallel region.")
	printf("===============================\n");
}
