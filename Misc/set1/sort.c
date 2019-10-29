#include <stdio.h>

void swap(int*, int*);
void sort(int*, int*, int, int, int);

int main()
{
  int arr[7] = {2,4,8,1,6,2,3};
  int perm[7];
  sort(arr, perm, 0, 6, 0);
  for (int i=0; i<7; i++) {
    printf("%i ", arr[perm[i]]);
  }
  printf("\n");
  return 0;
}

void swap(int *a, int *b) {
  int t=*a; *a=*b; *b=t;
}

void sort(int arr[], int perm[], int beg, int end, int c) {
  if (end > beg + 1) {
    int piv = arr[beg], l = beg + 1, r = end;
    while (l < r) {
      if (arr[l] <= piv)
        l++;
      else
        swap(&arr[l], &arr[--r]);
    }
    swap(&arr[--l], &arr[beg]);
    // printf("%i ", beg);
    // perm[c] = beg; c++;
    sort(arr, perm, beg, l, c);
    sort(arr, perm, r, end, c);
  }
}
