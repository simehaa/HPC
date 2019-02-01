#include <stdio.h>

double pow100(double x) {
  // 6 multiplications
  double x2,x4,x5,x25,x50;
  x2 = x*x;
  x4 = x2*x2;
  x5 = x4*x;
  x25 = x5*x5;
  x50 = x25*x25;
  return x50*x50;
}

int main() {
  double a = pow100(1.01);
  printf("%lf\n", a);
  return 0;
}
