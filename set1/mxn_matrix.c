#include <stdlib.h>
#include <stdio.h>

int main() {
  /* I will construct the following matrix:
   * [1 2 3]
   * [4 5 6]
   * by rows in outer loop and columns in inner loop
   * and opposite the following matrix:
   * [1 3 5]
   * [2 4 6]
   * by columns in outer loop and rows in inner loop.
   */

  // Rows then columns:
  int* mat;
  int m = 2;
  int n = 3;
  int elem = 1;
  mat = (int*) malloc(m * n * sizeof(int));
  // Fill matrix with elements:
  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      mat[i*n + j] = elem;
      elem++;
    }
  }
  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      printf("%d ",mat[i*n + j]);
    }
    printf("\n");
  }
  free(mat);

  // Columns then rows:
  printf("\n");
  int* mat2;
  elem = 1;
  mat2 = (int*) malloc(m * n * sizeof(int));
  // Fill matrix
  for (int j=0; j<n; j++) {
    for (int i=0; i<m; i++) {
      mat2[i + j*m] = elem;
      elem++;
    }
  }
  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      printf("%d ",mat2[i + j*m]);
    }
    printf("\n");
  }
  free(mat2);
  return 0;
}
