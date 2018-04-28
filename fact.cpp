#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <vector>
/*
* To work with big integers.
*/
#include <boost\multiprecision\cpp_int.hpp>

/*
* In order to compile the code,
* you need to install and build 
* Boost library for C++.
* http://www.boost.org/
* Regards,
* Ahmad Siavashi
*/

using namespace std;
using namespace boost::multiprecision;

int fact(const int N, cpp_int& result) {
	const auto max_num_threads = omp_get_max_threads();
	vector<cpp_int> partial_results(max_num_threads, 1);
	auto chunk = N / max_num_threads;
	omp_set_num_threads(max_num_threads);
#pragma omp parallel
	{
		auto tid = omp_get_thread_num();
		auto start = tid * chunk + 1;
		auto end = tid != max_num_threads -1 ? (tid + 1) * chunk : N;
#pragma omp parallel for
		for (auto i = start; i <= end; ++i) {
			partial_results[tid] *= i;
		}
	}
	result = 1;
	for (auto i = 0; i < max_num_threads; ++i) {
		result *= partial_results[i];
	}
	return EXIT_SUCCESS;
}

int main() {
	int N;
	cpp_int result;
	cout << "[-] please enter N: ";
	// get N
	cin >> N;
	auto s_time = omp_get_wtime();
	if (fact(N, result) == EXIT_SUCCESS) {
		auto e_time = omp_get_wtime();
		cout << "[-] computed successfully." << endl;
		// Too long to print
		// cout << "[-] factorial of " << N << " is " << result << endl;
		cout << "[-] measured execution time is " << e_time - s_time << " seconds." << endl;
	}
	else {
		cout << "[-] factorial computation failed." << endl;
	}
	return EXIT_SUCCESS;
}
