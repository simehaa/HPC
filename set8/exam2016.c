void para_matvec(int n, double**A, double*x, double*y) {
  int my_rank, num_procs;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  // broadcast
  if (my_rank == 0)
    MPI_Bcast();

  // muliplication
  for () {

  }

  // gather
  MPI_Gather();
}
