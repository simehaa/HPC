#include <stdio.h>
#include <time.h>

double numerical_integration(double x_min, double x_max, int slices)
{
  double delta_x = (x_max-x_min)/slices;
  double x, sum = 0.0;
  for (int i=0; i<slices; i++) {
    x = x_min + (i+0.5)*delta_x;
    sum = sum + 4.0/(1.0+x*x);
  }
  return sum*delta_x;
}

int main() {
  clock_t start;
  double flops_per_clock;
  for (int i=2; i<1025; i*=2) {
    start = clock();
    double result = numerical_integration(0,1.0,i);
    flops_per_clock = (3 + 7*i)/(clock()-start);
    printf("%4i slices, I = %1.6lf, rate = %1.2lf \n", i, result, flops_per_clock);
  }

  return 0;
}
