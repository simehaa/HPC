#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double pow100(double x) {
  double xp, x5;
  xp = x*x; // x^2
  xp *= xp;  // x^4
  x5 = x*xp; // x^5
  xp = x5*x5; // x^10
  xp *= xp; // x^20
  xp *= x5; // x^25
  xp *= xp; // x^50
  return xp*xp;
}

int main() {
  clock_t start;
  int n = 100000;
  int i;
  double time_elapsed1, time_elapsed2;
  double *number = malloc(n * sizeof *number);
  double *result = malloc(n * sizeof *result);
  for (i=0; i<n; i++) {
    number[i] = 1.001;
  }

  start = clock();
  for (i=0; i<n; i++) {
    result[i] = pow100(number[i]);
  }
  time_elapsed1 = (clock() - start);
  printf("pow100: result = %lf, time = %lf clock ticks\n", result[0], time_elapsed1);
  double old_res = result[0];

  start = clock();
  for (i=0; i<n; i++) {
    result[i] = pow(number[i],100);
  }
  time_elapsed2 = (clock() - start);
  printf("pow:    result = %lf, time = %lf clock ticks\n", result[0], time_elapsed2);

  if (fabs(old_res - result[0]) > 1e-6) {
    printf("Error, result not sufficiently accurate\n");
  }

  printf("Speedup = %lf\n", time_elapsed2/time_elapsed1);

  free(number);
  free(result);
  return 0;
}
