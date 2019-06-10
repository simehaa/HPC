#include "functions.h"

void setup_ranks(int *dim, int *period, int *coords, int m, int my_rank,
    int num_procs, int *l_m) {
  /* Function:
   * 1) Finds length of domains l_m
   * 2) Setup coords which contains indices in m-direction
   */
  (*l_m) = m/dim[0];
  int rest_m = m%dim[0];

  if (rest_m != 0) (*l_m)++;

  coords[0] = (*l_m)*my_rank; // start index in m-direction
  coords[1] = (*l_m)*(my_rank+1); // stop index + 1 in m-dir

  if (my_rank == num_procs-1) coords[1] = m;
  /* Image
   * |    ...   0   ...   |
   * |    ...   1   ...   |
   * |          :         |
   * |    num_procs - 1   |
   * a rank will use indices:
   * im = coords[0], ... , coords[1] - 1
   * in = 0, ... , n - 1
   */
}

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

void iso_diffusion_denoising_parallel(image *u, image *u_bar,
  float kappa, int maxiter, int my_rank, int num_procs) {

  int n = u->n, up = 0, down = (u->m)-1, odd, even;
  float *top = malloc(n*sizeof *top);
  float *bot = malloc(n*sizeof *bot);
  if (my_rank%2 == 0) {
    odd = 0;
    even = 1;
  } else {
    odd = 1;
    even = 0;
  }

  for (int iter=1; iter<=maxiter; iter++)
  {
    // Ghost layer communication and sweep
    if (odd)
        MPI_Recv(top,n,MPI_FLOAT,my_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    if (even && my_rank != num_procs-1)
        MPI_Send(u->image_data[down],n,MPI_FLOAT,my_rank+1,0,MPI_COMM_WORLD);
    if (even && my_rank)
        MPI_Recv(top,n,MPI_FLOAT,my_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    if (odd && my_rank != num_procs-1)
        MPI_Send(u->image_data[down],n,MPI_FLOAT,my_rank+1,0,MPI_COMM_WORLD);
    if (odd && my_rank != num_procs-1)
        MPI_Recv(bot,n,MPI_FLOAT,my_rank+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    if (even && my_rank)
        MPI_Send(u->image_data[up],n,MPI_FLOAT,my_rank-1,0,MPI_COMM_WORLD);
    if (even && my_rank != num_procs-1)
        MPI_Recv(bot,n,MPI_FLOAT,my_rank+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    if (odd)
        MPI_Send(u->image_data[up],n,MPI_FLOAT,my_rank-1,0,MPI_COMM_WORLD);

    // Sweep
    for (int i=1; i<(u->m-1); i++) { // every inner points in a chunk
      for (int j=1; j<n-1; j++) {
        u_bar->image_data[i][j] = u->image_data[i][j] + kappa*(
                                  u->image_data[i+1][j] + // above
                                  u->image_data[i-1][j] - // below
                                  4*u->image_data[i][j] +
                                  u->image_data[i][j+1] + // right
                                  u->image_data[i][j-1]); // left
      }
    }
    for (int j=1; j<n-1; j++) {
      if (my_rank != 0)
        u_bar->image_data[up][j] = u->image_data[up][j] + kappa*(top[j] + // above
                                   u->image_data[up+1][j] - // below
                                   4*u->image_data[up][j] +
                                   u->image_data[up][j+1] + // right
                                   u->image_data[up][j-1]); // left
      if (my_rank != num_procs-1)
        u_bar->image_data[down][j] = u->image_data[down][j] + kappa*(bot[j] + // below
                                     u->image_data[down-1][j] - // above
                                     4*u->image_data[down][j] +
                                     u->image_data[down][j+1] + // right
                                     u->image_data[down][j-1]); // left
    }
    // Update u
    if (iter < maxiter) { // this part is not needed at last step
      float **temp = u->image_data;
      u->image_data = u_bar->image_data;
      u_bar->image_data = temp;
    }
  }
}
