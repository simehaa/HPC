#include <stdio.h>

double powint(double x, int y) {
  if (y == 1) {
    return x;
  }
  return x*powint(x,--y);
}

int main() {
  double a = powint(2.0,100);
  printf("%lf\n", a);
  return 0;
}
