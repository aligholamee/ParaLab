#include <iostream>
#include <stdio.h>

using namespace std;

// Define the recursive fibonacci
int fib(int n) {
	if (n == 1 || n == 0)
		return 1;

	// If not
	return fib(n - 1) + fib(n - 2);
}

int main() {
	
	int num;

	cout << "Please enter a number: " << endl;
	cin >> num;

	cout << "Fibonacci final result: " << endl << fib(num) << endl;

	// Wait :)
	system("pause");

 	return 0;

}