#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
  clock_t start, end;
  long n = 1e6;
  char a[n], b[n], c[n];
  start = clock();
  for (long i=0; i<n; i++) b[i] = a[i];
  end = clock();
  double time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Time (for loop) = %lf\n", time);

  start = clock();
  memcpy(c, a, n);
  end = clock();
  time = (end - start)/(double)CLOCKS_PER_SEC;
  printf("Time (memcpy)   = %lf\n", time);
  return 0;
}

/*
Time (for loop) = 0.006218
Time (memcpy)   = 0.000398
*/
