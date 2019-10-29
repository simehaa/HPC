#include "functions.h"

void allocate_image(image *u, int m, int n) {
  u->m = m;
  u->n = n;
  u->image_data = malloc(m*sizeof u->image_data);
  for (int i=0; i<m; i++)
    u->image_data[i] = malloc(n*sizeof u->image_data[i]);
  // Allocation test
  if (!u->image_data[0] || !u->image_data)
    printf("Allocation failed\n");
}

void deallocate_image(image *u){
  for (int i=0; i<u->m; i++)
    free(u->image_data[i]);
  free(u->image_data);
}

void convert_jpeg_to_image(const unsigned char* image_chars, image *u) {
  for (int i=0; i<u->m; i++)
    for (int j=0; j<u->n; j++)
      u->image_data[i][j] = image_chars[i*u->n + j];
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars) {
  for (int i=0; i<u->m; i++)
    for (int j=0; j<u->n; j++)
      image_chars[i*u->n + j] = u->image_data[i][j];
}

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int maxiter) {

  for (int iter=1; iter<=maxiter; iter++)
  {
    // One sweep of the image
    for (int i=1; i<u->m-1; i++)
      for (int j=1; j<u->n-1; j++)
        u_bar->image_data[i][j] = u->image_data[i][j] + kappa*(
                                  u->image_data[i+1][j] +
                                  u->image_data[i-1][j] -
                                  4*u->image_data[i][j] +
                                  u->image_data[i][j+1] +
                                  u->image_data[i][j-1]);
    // Update u
    if (iter < maxiter) { // this part is not needed at last step
      float **temp = u->image_data;
      u->image_data = u_bar->image_data;
      u_bar->image_data = temp;
    }
  }
}
