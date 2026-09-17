 #include <stdio.h>
#include <omp.h>

int fib(int n) {
    int x, y;

    if (n <= 1)
        return n;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n;
    double start, end;

    printf("Enter number of Fibonacci terms: ");
    scanf("%d", &n);

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < n; i++) {
                #pragma omp task firstprivate(i)
                {
                    int result = fib(i);

                    #pragma omp critical
                    printf("fib(%d) = %d\n", i, result);
                }
            }
        }
    }

    end = omp_get_wtime();

    printf("Time taken: %f seconds\n", end - start);

    return 0;
}
