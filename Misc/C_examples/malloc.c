#include <stdlib.h>


int main () {
  // 1D Array
  int n_elements = 10;
  int *arr = malloc(n_elements * sizeof *arr);
  free(arr);

  // 2D Array
  double **arr2d;
  int m=2, n=4;
  arr2d = malloc(m * sizeof *arr2d);
  arr2d[0] = malloc(m*n * sizeof *arr2d[0]);

  for (int i=1; i<m; i++) {
    arr2d[i] = &(arr2d[0][i*n]);
  }
  // Can now be used with syntax: arr[i][j]
  free(arr2d[0]);
  free(arr2d);

  // 3D Array
  int ***A;
  int nx=3, ny=3, nz=3;
  A = malloc(nz * sizeof *A);
  A[0] = malloc(nz*ny * sizeof *A[0]);

  for (int i=1; i<nz; i++) {
    A[i] = &A[0][i*ny];
  }

  A[0][0] = malloc(nz*ny*nx * sizeof *A[0][0]);

  for (int j=1; j<nz*ny; j++) {
    A[0][j] = &A[0][0][j*nx];
  }

  // Can now be use with syntax A[x][y][z];

  free(A[0][0]);
  free(A[0]);
  free(A);

  // Alternative
  // 3D:
  #define index(i,j,k) (i*ny*nz + j*nz + k)
  // 2D:  index(i,j)   (i*ny + j)
  int *matrix = malloc(nx*ny*nz * sizeof *matrix);

  for (size_t i=0; i<nx; i++) {
    for (size_t j=0; j<ny; j++) {
      for (size_t k=0; k<nz; k++) {
        matrix[index(i,j,k)] = i + j + k;
      }
    }
  }

  free(matrix);
  return 0;
}

// valgrind --leak-check=full ./a.out
