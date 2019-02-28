// Some helper functions for week 5. Most of these functions are the same as
// those in week4.h

#include <stdlib.h> // malloc and free.
#include <stdio.h>  // printf

int alloc2D(double ***A, int n, int m)
{
    *A = malloc(n * sizeof *A);
    (*A)[0] = malloc(n*m * sizeof (*A)[0]);
    if (!(*A)[0] || !*A){
        // Allocation failed.
        printf("Allocation failed\n");
        return 1;
    }

    for (size_t i = 1; i < n; i++) {
        (*A)[i] = &((*A)[0][i*m]);
    }
    return 0;
}

// Free pointers allocated in alloc2D.
int free2D(double **A)
{
    free(A[0]);
    free(A);
    return 0;
}

// Print matrix values.
int printmat(double **A, int n, int m)
{
    for (size_t i = 0; i < n; ++i){
        printf("| ");
        for (size_t j = 0; j < m; ++j){
            printf("%4.1lf ", A[i][j]);
        }
        printf("|\n");
    }
    return 0;
}


int printvec(double *y, int N)
{
    printf("(");
    for (size_t i = 0; i < N-1; i++) {
        printf("%4.1lf, ", y[i]);
    }
    printf("%3.1lf", y[N-1]);
    printf(")\n");
    return 0;
}
