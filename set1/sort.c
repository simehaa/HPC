int main() {
  int arr[7] = {2,4,8,1,6,2,3};
  sort()
  return 0;
}

void swap(int *a, int *b) {
  int t=*a; *a=*b; *b=t;
}

void sort(int arr[], int beg, int end) {
  if (end > beg + 1) {
    int piv = arr[beg], l = beg + 1, r = end;
    while (l < r) {
      if (arr[l] <= piv)
        l++;
      else
        swap(&arr[l], &arr[--r]);
    }
    swap(&arr[--l], &arr[beg]);
    sort(arr, beg, l);
    sort(arr, r, end);
  }
}
