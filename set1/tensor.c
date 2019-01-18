#include <stdlib.h>
#include <stdio.h>

int main() {
  /*
   * A construction of a 3D array
   */

  int* cube;
  int nx=3, ny=3, nz=2;
  cube = (int*) malloc(nx*ny*nz*sizeof(int));

  // filling of tensor elements
  for (int k=0; k<nz; k++) {
    for (int j=0; j<ny; j++) {
      for (int i=0; i<nx; i++) {
        cube[i + j*nx + k*nx*ny] = i*ny*nz + j*nz + k;
      }
    }
  }

  // printing of the tensor
  for (int k=0; k<nz; k++) {
    printf("\nSlice %d:\n", k);
    for (int j=0; j<ny; j++) {
      for (int i=0; i<nx; i++) {
        printf(" %d", cube[i + j*nx + k*nx*ny]);
      }
      printf("\n");
    }
  }

  free(cube);
  return 0;
}
