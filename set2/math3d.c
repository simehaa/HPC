#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {
  double* v;
  double* u;
  int nx=10, ny=10, nz=10;
  v = (double*) calloc(nx*ny*nz, sizeof(double));
  u = (double*) calloc(nx*ny*nz, sizeof(double));

  for (int i=0; i<nx; i++) {
    for (int j=0; j<ny; j++) {
      for (int k=0; k<nz; k++) {
        v[i + j*ny + k*ny*nz] = 2 + sin(i*j*k*M_PI/((nx-1)*(ny-1)*(nz-1)));
      }
    }
  }
  int mid, left, right, up, down, front, back;
  int itermax = 10;

  for (int iter=0; iter<itermax; iter++)
  {
    // Algorithm for updating u
    for (int i=1; i<nx-1; i++) {
      for (int j=1; j<ny-1; j++) {
        for (int k=1; k<nz-1; k++) {
          mid = i + j*ny + k*ny*nz;
          left = mid - 1;
          right = mid + 1;
          up = i + (j+1)*ny + k*ny*nz;
          down = i + (j-1)*ny + k*ny*nz;
          front = i + j*ny + (k-1)*ny*nz;
          back = i + j*ny + (k+1)*ny*nz;
          u[mid]  = v[mid] + (v[left] + v[right] + v[down] + v[up] + v[back] + v[front] - 6*v[back])/6.0;
        }
      }
    }
    for (int i=0; i<nx; i++) {
      for (int j=0; j<ny; j++) {
        for (int k=0; k<nz; k++) {
          mid = i + j*ny + k*ny*nz
          v[mid] = u[mid];
        }
      }
    }
  }

  free(u); free(v);

  return 0;
}
