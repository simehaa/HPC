#include <stdio.h>
#include <stdlib.h>

#define index(i,j,ny) (i*ny + j)

int main() {
  int n=2,m=2,p=2; // A (n X m) and B (m X p)
  double *A = malloc(n * m * sizeof *A);
  double *B = malloc(m * p * sizeof *B);
  double *C = malloc(n * p * sizeof *C);
  double elem;

  // Fill A
  A[index(0,0,m)] = 2; // [2  3]
  A[index(0,1,m)] = 3; // [4  1]
  A[index(1,0,m)] = 4;
  A[index(1,1,m)] = 1;
  // Fill B
  B[index(0,0,p)] = -1; // [-1 2]
  B[index(0,1,p)] = 2; //  [1  3]
  B[index(1,0,p)] = 1;
  B[index(1,1,p)] = 3;

  // Matrix matrix multiplication
  for (int i=0; i<n; i++) {
    for (int j=0; j<p; j++) {
      // Currently at 1 matrix elem in C-matrix
      elem = 0;
      for (int k=0; k<m; k++) {
        elem += A[index(i,k,m)]*B[index(k,j,p)];
      }
      C[index(i,j,p)] = elem;
      printf("%lf ", C[index(i,j,p)]);
    }
    printf("\n");
  }

  free(A);
  free(B);
  free(C);
  return 0;
}
