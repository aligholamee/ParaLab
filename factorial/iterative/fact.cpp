#include <iostream>
#include <omp.h>

using namespace std;

#define NUM_THREADS 2

int fact(int n);

int main() {

    int num; 
    cin >> num;

    float start_time = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS);

    int fact_result = 1;

    int job_size = 0;
    int job_start = 1;
    int job_end = 0;
    // Each thread creates its own fact computation result
    int thread_fact = 1;

    #pragma omp parallel firstprivate(job_size, job_start, job_end, thread_fact)
    {
        int thread_id = omp_get_thread_num() + 1;
        job_size = num / omp_get_num_threads();

        // Final thread has excessive load
        if(num % omp_get_num_threads() && thread_id == 1) 
            job_size += num % omp_get_num_threads();

        #pragma omp critical
        {
            cout << "\n[INFO] T["<<thread_id<<"] Job Size = ["<<job_size<<"]\n" << endl;
        }
        
        // Define the limits!
        if(thread_id != 1) {
            job_start = (thread_id * job_size)
        }
        job_end = job_start + job_size;



        #pragma omp critical
        {
            cout << "\n[INFO] T["<<thread_id<<"] Starts from = ["<<job_start<<"]\n" << endl;
            cout << "\n[INFO] T["<<thread_id<<"] Ends to = ["<<job_end<<"]\n" << endl;
        }

        for(int i = job_start; i <= job_end; i++) {
            // Compute the chunk of factorial
            thread_fact = thread_fact * i;
        }

        #pragma omp critical
        {
            cout << "\n[INFO] T["<<thread_id<<"] result = "<<thread_fact<<"\n" << endl;
        }


        // Combine the facts
        #pragma omp barrier

        for(int i = 0; i < omp_get_num_threads() - 1; i++) {
            

            // Each thread multiples + writes its value and goes away :))
            #pragma omp critical
            {
                fact_result *= thread_fact;
            }
        }
        
    }

    // Print the results
    cout << "Factorial of " << num << ": " << fact_result << endl;
    
    // Get the elapsed time
    float elapsed_time = omp_get_wtime() - start_time;

    cout << "Elapsed time is: " << elapsed_time << endl;
    return 0;
}