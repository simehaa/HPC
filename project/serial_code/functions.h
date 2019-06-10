#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  float** image_data;
  int m, n;
}
image;

void allocate_image(image *u, int m, int n);
void deallocate_image(image *u);
void convert_jpeg_to_image(const unsigned char* image_chars, image *u);
void convert_image_to_jpeg(const image *u, unsigned char* image_chars);
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int maxiter);
void import_JPEG_file(const char* filename, unsigned char** image_chars,
              int* image_m, int* image_n, int* num_conents);
void export_JPEG_file(const char* filename, const unsigned char* image_chars,
              int image_m, int image_n, int num_conents, int quality);

#endif // FUNCTIONS_H
