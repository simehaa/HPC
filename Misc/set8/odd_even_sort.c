#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void serial_odd_even(int, int*);
void compare(int*, int, int);
void print_a(int, int*);
void test_a(int, int*);

int main(int argc, char** argv) {
  int n = 100;
  int *a = malloc(n * sizeof *a);
  time_t t;
  srand((unsigned) time(&t));
  // initialize some values

  for (int i=0; i<n; i++) {
    a[i] = rand()%100;
  }
  print_a(n,a);
  serial_odd_even(n,a);
  print_a(n,a);
  test_a(n,a);

  free(a);
  return 0;
}

void serial_odd_even(int n, int *a) {
  if (n%2 == 1) n++; // to ensure lists of odd length
  // have enough indices for algorithm

  for (int i=0; i<n; i++) {
    if (i%2 == 1) { // odd
      for (int j=0; j<n/2; j++) {
        compare(a,2*j+1,2*j+2);
      }
    } else { // even
      for (int j=0; j<n/2; j++) {
        compare(a,2*j,2*j+1);
      }
    }
  }
}

void compare(int *a, int beg, int end) {
  if (a[beg] > a[end]) {
      int t = a[beg];
      a[beg] = a[end];
      a[end] = t;
  }
}

void print_a(int n, int *a) {
  printf("[");
  for (int i=0; i<n-1; i++) printf("%d, ",a[i]);
  printf("%d]\n",a[n-1]);
}

void test_a(int n, int *a) {
  for (int i=0; i<n-1; i++) {
    if (a[i] > a[i+1]) {
      printf("Error: function not sorted properly\n");
      printf("a[%i]=%i and a[%i]=%i\n",i,a[i],i+1,a[i+1]);
      exit(0);
    }
  }
}
