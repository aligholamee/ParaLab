/*
*				In His Exalted Name
*	Title:	MergeSort Sequential Code
*	Author: Ahmad Siavashi, Email: siavashi@aut.ac.ir
*	Date:	24/11/2015
*	Parallelization: Ali Gholami (aligholami7596@gmail.com)
*/

// Let it be.
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define MAX(A, B) ((A)>(B))?(A):(B)
#define MIN(A, B) ((A)<(B))?(A):(B)

void printArray(int *array, int size);
void fillArray(int *array, int size);
void merge(int *a, int n, int m);
void mergeSort(int *a, int n);


int main(int argc, char *argv[]) {
	int *array = NULL;
	int size = 0;
	if (argc < 2) {
		printf("[-] Invalid No. of arguments.\n");
		printf("[-] Try -> <size_of_array>\n");
		printf(">>> ");
		scanf("%d", &size);
	}
	else {
		size = atoi(argv[1]);
	}
	array = (int *)malloc(sizeof(int) * size);

	// Run it 6 times
	int NUM_RUNS = 6;
	double TOTAL_TIME = 0.0;

	for(int i = 0; i < NUM_RUNS; i++) {

		fillArray(array, size);
		printf("Merge Sort:\n");

		// Start the timer

		double start_time = omp_get_wtime();

		mergeSort(array, size);

		// Finish the timer
		double elapsed_time = start_time - omp_get_wtime();
		TOTAL_TIME += elapsed_time;

		printArray(array, size);

		free(array);
	}

	print("Average run time[6 Iterations]: %lf", TOTAL_TIME / NUM_RUNS);

	system("PAUSE");
	return EXIT_SUCCESS;
}

void fillArray(int *array, int size) {
	srand(time(NULL));
	while (size-->0) {
		*array++ = rand() % 100;
	}
}

void printArray(int *array, int size) {
	while (size-->0) {
		printf("%d, ", *array++);
	}
	printf("\n");
}

void merge(int *a, int n, int m) {
	int i, j, k;
	int *temp = (int *)malloc(n * sizeof(int));
	for (i = 0, j = m, k = 0; k < n; k++) {
		temp[k] = j == n ? a[i++]
			: i == m ? a[j++]
			: a[j] < a[i] ? a[j++]
			: a[i++];
	}
	for (i = 0; i < n; i++) {
		a[i] = temp[i];
	}
	free(temp);
}

void mergeSort(int *a, int n) {
	int m;
	if (n < 2)
		return;
	m = n / 2;
	mergeSort(a, m);
	mergeSort(a + m, n - m);
	merge(a, n, m);
}
