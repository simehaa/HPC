#include "functions.h"

int main(int narg, char** argv) {
  if (narg != 5) {
    printf("Error, wrong usage! \nProvide 4 arguments:\n");
    printf("$ ./serial_main kappa maxiter infile outfile\n");
    exit(1);
  }

  int m, n, c;
  float kappa = atof(argv[1]);
  int maxiter = atoi(argv[2]);
  char *infile = argv[3];
  char *outfile = argv[4];
  image u, u_bar;
  unsigned char *image_chars;
  struct timespec start, end;

  import_JPEG_file(infile, &image_chars, &m, &n, &c);
  if (c != 1) printf("Warning: not a grayscale image");
  printf("Image %s (%d x %d) imported.\n", infile, m, n);
  allocate_image(&u, m, n);
  allocate_image(&u_bar, m, n);
  convert_jpeg_to_image(image_chars, &u);


  clock_gettime(CLOCK_MONOTONIC, &start);
  iso_diffusion_denoising(&u, &u_bar, kappa, maxiter);
  clock_gettime(CLOCK_MONOTONIC, &end);
  double algo_time = (end.tv_sec-start.tv_sec)+1e-9*(end.tv_nsec-start.tv_nsec);
  convert_image_to_jpeg(&u_bar, image_chars);
  export_JPEG_file(outfile, image_chars, m, n, c, 75);
  deallocate_image(&u);
  deallocate_image(&u_bar);
  free(image_chars);

  printf("Image %s (%d x %d) exported.\n", outfile, m, n);
  printf("Time of function iso_diffusion_denoising(): %1.2f s\n", algo_time);

  return 0;
}
