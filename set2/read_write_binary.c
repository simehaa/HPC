#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  clock_t start, end;
  double* arr;
  arr = (double*) malloc(1e6*sizeof(double));

  start = clock();
  
  end = clock();
  free(arr);
  double time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Time = %lf\n", time);
  return 0;
}
