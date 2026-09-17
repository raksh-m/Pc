#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    int *t = malloc((r - l + 1) * sizeof(int));

    while (i <= m && j <= r)
        t[k++] = (a[i] < a[j]) ? a[i++] : a[j++];

    while (i <= m) t[k++] = a[i++];
    while (j <= r) t[k++] = a[j++];

    for (i = l, k = 0; i <= r; i++, k++)
        a[i] = t[k];

    free(t);
}

void mergeSort(int a[], int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}

void parallelSort(int a[], int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSort(a, l, m);

        #pragma omp section
        mergeSort(a, m + 1, r);
    }

    merge(a, l, m, r);
}

int main() {
    int n;
    double start, end, seq, par;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    int *b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000;
        b[i] = a[i];
    }

    // Sequential Merge Sort
    start = omp_get_wtime();
    mergeSort(a, 0, n - 1);
    end = omp_get_wtime();
    seq = end - start;

    // Parallel Merge Sort
    start = omp_get_wtime();
    parallelSort(b, 0, n - 1);
    end = omp_get_wtime();
    par = end - start;

    printf("Sequential time: %f seconds\n", seq);
    printf("Parallel time: %f seconds\n", par);
    printf("Speedup: %f\n", seq / par);

    free(a);
    free(b);

    return 0;
}
