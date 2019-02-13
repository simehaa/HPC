#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int narg, char* argv[]) {
  int i,n;
  if (narg < 2) {
    printf("ERROR, Wrong usage: enter number (length of array)\n");
    exit(0);
  }

  n = atoi(argv[1]);
  clock_t start;
  double s = 2.5, time_elapsed;
  double *A = malloc(n * sizeof *A);
  double factor = 1.0/n;
  for (i=0; i<n; i++){
    A[i] = i*factor; // fill some values
  }
  double *B = malloc(n * sizeof *B);

  // Normal for loop
  start = clock();
  for (i=0; i<n; i++){
    A[i] = s*B[i];
  }
  time_elapsed = (clock() - start)/(double) CLOCKS_PER_SEC;
  double performance = n/(time_elapsed*1e9);
  printf("Performance (Normal) = %lf GFlops/sec\n", performance);

  // Strided for loop
  int stride = 5;
  start = clock();
  for (i=0; i<n; i+=stride){
    A[i] = s*B[i];
  }
  time_elapsed = (clock() - start)/(double) CLOCKS_PER_SEC;
  performance = n/(time_elapsed*1e9*stride);
  printf("Performance (Strided) = %lf GFlops/sec\n", performance);

  free(A);
  free(B);
  return 0;
}
