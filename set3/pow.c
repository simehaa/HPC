#include <stdio.h>

double powint(double x, int y) {
  if (y == 1) {
    return x;
  }
  return x*powint(x,--y);
}

int main() {
  int a = powint(2,5);
  printf("%d\n", a);
  return 0;
}
