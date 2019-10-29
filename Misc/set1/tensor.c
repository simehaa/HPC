#include <stdlib.h>
#include <stdio.h>

int main() {
  /*
   * A construction of a 3D array
   */

  int nx=3, ny=3, nz=2;
  int *cube = malloc(nx*ny*nz*sizeof(int));

  #define index(i,j,k) (i*ny*nz + j*nz + k)

  for (int i=0; i<nx; i++) {
    for (int j=0; j<ny; j++) {
      for (int k=0; k<nz; k++) {
        cube[index(i,j,k)] = i + j + k;
      }
    }
  }

  free(cube);
  return 0;
}
