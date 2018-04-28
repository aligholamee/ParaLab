#include <cstdlib>
#include <omp.h>
#include <iostream>
#include <boost\multiprecision\cpp_int.hpp>
/*
* To work with big integers.
*/
using namespace std;
using namespace boost::multiprecision;

/*
* In order to compile the code,
* you need to install and build 
* Boost library for C++.
* http://www.boost.org/
* Regards,
* Ahmad Siavashi
*/

cpp_int fib(int n) {
	cpp_int f[6]{ 1,1 };
	int max_term = 1;
#pragma omp parallel
	do {
#pragma omp single nowait
		f[2] = f[1] + f[0];
#pragma omp single nowait
		f[3] = f[1] * 2 + f[0];
#pragma omp single nowait
		f[4] = f[1] * 3 + f[0] * 2;
#pragma omp single nowait
		f[5] = f[1] * 5 + f[0] * 3;
#pragma omp barrier
#pragma omp single
		{
			max_term += 4;
			if (max_term < n) {
				f[0] = f[4];
				f[1] = f[5];
			}
		}
	} while (max_term < n);
	return f[5 - (max_term - n)];
}

int main() {
	auto n = 0;
	while (true) {
		cout << "[-] Please enter n: ";
		cin >> n;
		if (n < 0) {
			cout << "[-] quit." << endl;
			break;
		}
		omp_set_num_threads(4);
		auto s_time = omp_get_wtime();
		auto result = fib(n);
		//cout << "[-] fib(n) is " << result << endl;
		auto e_time = omp_get_wtime();
		cout << "[-] execution time was " << e_time - s_time << "s" << endl;
	}
	return EXIT_SUCCESS;
}
