/*
* In his exalted name
*
* Reduction - Sequential Code
* Written by Ahmad Siavashi (siavashi@aut.ac.ir)
* Date: June, 2018
* Language: C++11
*/
#include <cstdlib>
#include <vector>
#include <chrono>
#include <iostream>>
#include <cmath>
#include <numeric>

// N = 2^22
#define N pow(2, 22)

using namespace std;

int main(int argc, char *argv[]) {
	// initialize a vector of size N with 1
	vector<int> v(N, 1);
	// capture start time
	auto start_time = chrono::high_resolution_clock::now();
	// reduction
	auto sum = accumulate(begin(v), end(v), 0);
	// capture end time
	auto end_time = chrono::high_resolution_clock::now();
	// elapsed time in milliseconds
	auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
	// print sum and elapsed time
	cout << "[-] Sum: " << sum << endl;
	cout << "[-] Duration: " << duration.count() << "ms" << endl;
	return EXIT_SUCCESS;
}
