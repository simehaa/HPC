#include <stdio.h>
#include <math.h>

void test_sum(int);

int main() {
  int iter;
  printf("Enter the number of iterations for the sum \n");
  scanf("%d", &iter);
  test_sum(iter);
  return 0;
}

void test_sum(int maxiter) {
  int n=0;
  double sum=0, tolerance=1e-6, factor=1;
  while (n++ < maxiter && fabs(0.8 - sum) > tolerance) {
    sum += factor;
    factor *= -0.25;
  }
  if (fabs(0.8 - sum) > tolerance) {
    printf("Error, Sum = %1.6f != 4/5, with %i iterations\n", sum, maxiter);
  }
}
