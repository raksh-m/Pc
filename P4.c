#include <stdio.h>
#include <math.h>
#include <omp.h>

int prime(int n) {
    if (n < 2) return 0;

    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return 0;

    return 1;
}

int main() {
    int n;
    double start, end, serial, parallel;

    printf("Enter n: ");
    scanf("%d", &n);

    // Serial
    start = omp_get_wtime();

    for (int i = 1; i <= n; i++)
        if (prime(i))
            printf("%d ", i);

    end = omp_get_wtime();
    serial = end - start;

    printf("\n");

    // Parallel
    start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 1; i <= n; i++) {
        if (prime(i)) {
            #pragma omp critical
            printf("%d ", i);
        }
    }

    end = omp_get_wtime();
    parallel = end - start;

    printf("\nSerial time: %f seconds\n", serial);
    printf("Parallel time: %f seconds\n", parallel);
    printf("Speedup: %f\n", serial / parallel);

    return 0;
}
