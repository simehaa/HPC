#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
  /* Generate an array at runtime, which is filled with 
   * random numbers 0-1, then the max and min value is printed
   */
  int length;
  srand (time(NULL));

  printf("Enter length of array (1-10,000)\n");
  scanf("%d", &length);
  if (length < 1 || length > 10000) exit(1);

  double arr[length];
  for (int i=0; i<length; i++) {
    arr[i] = (double)rand()/RAND_MAX; // random numbers in range 0-1
  }

  double min=100;
  double max=0;
  for (int i=0; i<length; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  printf("max = %f\n", max);
  printf("min = %f\n", min);
  return 0;
}
