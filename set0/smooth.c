#include <stdio.h>
#include <stdlib.h>

double* smooth(double*, int, int, double);
void printmatrix(double*, int, int);

int main() {
  double* matrix_old;
  int nrows = 6;
  int ncols = 6;
  const double c = 1.2;
  matrix_old = (double*) malloc(nrows*ncols*sizeof(double));
  for (int i=0; i<nrows; i++) {
    for (int j=0; j<ncols; j++) {
      matrix_old[i*nrows + j] = (i-2.5)*(i-2.5)*(j-2.5);
    }
  }
  printmatrix(matrix_old, nrows, ncols);
  double* matrix_new = smooth(matrix_old, nrows, ncols, c);
  printmatrix(matrix_new, nrows, ncols);
  free(matrix_old);
  free(matrix_new);
  return 0;
}

double* smooth(double* u, int nrows, int ncols, double c) {
  /* Applies the smooth function to input matrix u with shape (nrows X ncols)
   * Returns matrix with same shape (indexed with rows as outer loop and
   * columns as inner loop)
   * Smooth function: v_ij = u_ij + c(u_i-1j + u_ij-1 - 4u_ij + uij+1 + ui+1j)
   * Boundaries kept fixed.
   */
  double* matrix_new;
  matrix_new = (double*) malloc(nrows*ncols*sizeof(double));

  // Copy matrix for all points
  for (int i=0; i<nrows; i++) {
    for (int j=0; j<ncols; j++) {
      matrix_new[i*nrows + j] = u[i*nrows + j];
    }
  }
  // Inner points
  for (int i=1; i<nrows-1; i++) {
    for (int j=1; j<ncols-1; j++) {
      matrix_new[i*nrows + j] += c*(u[(i-1)*nrows + j] + u[i*nrows + j - 1] -
        4*u[i*nrows + j] + u[(i+1)*nrows + j] + u[i*nrows + j + 1]);
    }
  }
  return matrix_new;
}

void printmatrix(double* matrix, int nrows, int ncols) {
  /* Prints a matrix which is shaped (nrows X ncols) and
   * indexed with rows as outer loop and columns as inner loop
   */
  for (int i=0; i<nrows; i++) {
    for (int j=0; j<ncols; j++) {
      printf("%f ",matrix[i*nrows + j]);
    }
    printf("\n");
  }
  printf("\n");
}
