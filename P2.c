#include <stdio.h>
#include <omp.h>

int main() {
    int n;

    // Ask user for number of iterations
    printf("Enter number of iterations: ");
    scanf("%d", &n);

    // Set number of threads via environment or manually
    omp_set_num_threads(4); // You can adjust this as needed

    // Parallel for loop with static scheduling and chunk size 2
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        // Each thread will report which iterations it executes
        #pragma omp for schedule(static,2)
        for (int i = 0; i < n; i++) {
            printf("Thread %d : Iteration %d\n", tid, i);
        }
    }

    return 0;
}
