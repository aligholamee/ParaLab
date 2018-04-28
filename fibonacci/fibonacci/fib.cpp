#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

// Let it be...
#define MAX_THREADS 8

// Define the recursive fibonacci
int fib(int n);

int main() {

	int num;

	cout << "Please enter a number: " << endl;
	cin >> num;

	float time_start = omp_get_wtime();

	// Set the number of threads :)
	omp_set_num_threads(MAX_THREADS);

	cout << "Fibonacci final result: " << endl << fib(num) << endl;

	float elapsed_time = omp_get_wtime() - time_start;
	cout << "Computation time: " << elapsed_time << endl;

	// Wait :)
	system("pause");

	return 0;
}

int fib(int n) {

#pragma omp parallel
		{

#pragma omp master
			{
				if (n == 1 || n == 0)
					return 1;

				// If not
				return fib(n - 1) + fib(n - 2);
			}

		}

	}