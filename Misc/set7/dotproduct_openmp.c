#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int N = 1000000, i;
  double s = 0;
  double *a = malloc(N * sizeof *a);
  double *b = malloc(N * sizeof *b);
  // initialize some values
  for (i=0; i<N; i++) {
    a[i] = i*0.1;
    b[i] = (N-i)*0.3;
  }
  struct timeval start, end;

  // Normal dot product
  gettimeofday(&start, NULL);
  for (i=0; i<N; i++) {
    s += a[i] * b[i];
  }
  gettimeofday(&end, NULL);
  double tot = (double)(end.tv_sec - start.tv_sec)*0.001; // ms
  printf("Normal, s=%lf ms", tot);

  free(a);
  free(b);
  return 0;
}
