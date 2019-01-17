#include <stdio.h>
#include <math.h>

double sum(int);

int main() {
  int iter;
  printf("Enter the number of iterations for the sum \n");
  scanf("%d", &iter);
  if (iter > 1 && iter < 1000) {
    printf("Sum = %f \n", sum(iter));
  } else {
    printf("Between 1 and 1000 iterations should be entered\n");
  }
  return 0;
}

double sum(int iter) {
  double sum = 1;
  int pm = -1;
  for (int i=2; i<2*iter; i+=2) {
    sum += pm / (double) pow(2.0,i);
    pm *= -1;
  }
  return sum;
}
