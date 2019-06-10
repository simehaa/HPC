#include "functions.h"

int main(int narg, char** argv) {
  // Initialization
  int my_rank,num_procs,m,n,c,maxiter,my_m,l_m,dim[2],period[2],coords[2];
  dim[0] = 0; dim[1] = 1; period[0] = 0; period[1] = 0;
  image u, u_bar;
  float kappa;
  unsigned char *image_chars;
  char *infile, *outfile;
  struct timespec start, end;

  // MPI initialization
  MPI_Init(&narg, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

  if (my_rank == 0) {
    if (narg != 5) {
      printf("Error, wrong usage! Provide following arguments:\n");
      printf("$ mpirun -np num_procs kappa maxiter infilename outfilename\n");
    }
  }

  // Command line arguments
  kappa = atof(argv[1]);
  maxiter = atoi(argv[2]);
  infile = argv[3];
  outfile = argv[4];

  // Import whole image
  if (my_rank == 0) {
    import_JPEG_file(infile, &image_chars, &m, &n, &c);
    if (c != 1) printf("Warning: not a grayscale image\n");
  }

  // Communicate and decompose domainPI_Cart_creat
  MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Dims_create(num_procs,2,dim);

  if (my_rank == 0) {
    printf("Domain decomposition: %d x %d\n",dim[0],dim[1]);
  }

  // Setup of domains
  setup_ranks(dim, period, coords, m, my_rank, num_procs, &l_m);
  my_m = coords[1] - coords[0];
  int size = my_m*n, send_counts[num_procs], displ[num_procs];
  for (int i=0; i<num_procs; i++) displ[i] = n*l_m*i;
  unsigned char *my_image_chars = malloc(size*sizeof *my_image_chars);
  // collect send_counts array (contains total size for each process)
  MPI_Gather(&size,1,MPI_INT,send_counts,1,MPI_INT,0,MPI_COMM_WORLD);
  // Scatter the 1D image_char array to all processes
  MPI_Scatterv(image_chars,send_counts,displ,MPI_UNSIGNED_CHAR,
            my_image_chars,size,MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

  allocate_image(&u, my_m, n);
  allocate_image(&u_bar, my_m, n);
  convert_jpeg_to_image(my_image_chars, &u);
  clock_gettime(CLOCK_MONOTONIC, &start);
  iso_diffusion_denoising_parallel(&u,&u_bar,kappa,maxiter,my_rank,num_procs);
  clock_gettime(CLOCK_MONOTONIC, &end);
  double algo_time = (end.tv_sec-start.tv_sec)+1e-9*(end.tv_nsec-start.tv_nsec);
  convert_image_to_jpeg(&u_bar, my_image_chars);
  MPI_Gatherv(my_image_chars,size,MPI_UNSIGNED_CHAR,image_chars,send_counts,
    displ,MPI_UNSIGNED_CHAR,0,MPI_COMM_WORLD);

  if (my_rank == 0) {
    export_JPEG_file(outfile, image_chars, m, n, c, 75);
    free(image_chars);
    printf("Time of function iso_diffusion_denoising_parallel(): %1.3f s\n",
      algo_time);
  }

  free(my_image_chars);
  deallocate_image(&u);
  deallocate_image(&u_bar);
  MPI_Finalize();

  return 0;
}
