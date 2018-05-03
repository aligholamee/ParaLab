#include <iostream>
#include <omp.h>

using namespace std;

#define NUM_THREADS 4

int fact(int n);

int main() {

    int num; 
    cin >> num;

    float start_time = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS);

    int fact_result = 1;

    int job_size = 0;
    int job_start = 0;
    int job_end = 0;

    #pragma omp parallel private(job_size, job_start, job_end)
    {
        // Each thread creates its own fact computation result
        int thread_fact = 1;

        int thread_id = omp_get_thread_num();
        job_size = num / omp_get_num_threads();

        // Make sure the job size is done until here
        pragma_omp_flush(job_size);

        // Final thread has excessive load
        if(num % omp_get_num_threads() && thread_id == omp_get_num_threads() - 1) 
            job_size += num % omp_get_num_threads();

        pragma_omp_flush(job_size);
        
        // For the last thread
        if(thread_id == omp_get_num_threads() - 1) {
            job_start = thread_id * job_size;
            job_end = job_start + job_size_last_thread;

        } else {

            // For other threads
            job_start = thread_id * job_size;
            job_end = job_start + job_size;
        }

        for(int i = job_start; i < job_size; i++) {
            // Compute the chunk of factorial
            thread_fact *= ++thread_fact;
        }

        // Combine the facts 
        for(int i = 0; i < omp_get_num_threads(); i++) {

            // Each thread multiples + writes its value and goes away :))
            #pragma omp critical
            {
                fact_result *= thread_fact;
            }
        }
        
    }

    for(int i = 0; i < num; i++) {
        
    }
    cout << "Factorial of " << num << ": " << fact_result << endl;
    
    // Get the elapsed time
    float elapsed_time = omp_get_wtime() - start_time;

    cout << "Elapsed time is: " << elapsed_time << endl;
    return 0;
}