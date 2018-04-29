#include <iostream>
#include <omp.h>

using namespace std;

#define NUM_THREADS 4

long long fact(int n);

int main() {

    int num; 
    cin >> num;

    float start_time = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS);

    cout << "Factorial of " << num << ": " << fact(num) << endl;
    
    // Get the elapsed time
    float elapsed_time = omp_get_wtime() - start_time;

    cout << "Elapsed time is: " << elapsed_time << endl;
    return 0;
}

long long fact(int n) {

    if(n == 0)
        return 1;
    
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            int a = n;

            #pragma omp task
            int b = fact(n - 1);
            int c = a * b;
        }
        
        int c = a * b;
    }
    
    // If not :)
    return n * fact(n - 1);
}