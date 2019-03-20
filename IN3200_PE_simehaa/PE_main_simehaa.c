#include <stdlib.h>
#include <stdio.h>

#include "PE_functions_simehaa.h"

int main(int argc, char **argv) {
  if (argc < 5) {
    printf("Usage error:\n");
    printf("$ ./pagerank.exe filename dampConst threshold nTopWebpages\n");
    exit(0);
  }
  char* filename = argv[1];
  double dampConst = atof(argv[2]);
  double threshold = atof(argv[3]);
  int nTopWebpages = atoi(argv[4]);
  int n = 0;
  int e = 0;
  int maxEdges = 0; // unspecified if 0
  int numDangling = 0;
  double* val = NULL;
  int* col_idx = NULL;
  int* row_ptr = NULL;
  int* dangling_idx = NULL;

  struct timespec start, end;

  clock_gettime(CLOCK_REALTIME, &start);
  read_graph_from_file(filename, &n, &e, maxEdges, &numDangling, &val, &col_idx,
    &row_ptr, &dangling_idx);
  clock_gettime(CLOCK_REALTIME, &end);
  double accum = (end.tv_sec-start.tv_sec) + 1e-9*(end.tv_nsec-start.tv_nsec);
  printf("read_graph_from_file, time = %lf s\n", accum);

  double *x = malloc(n * sizeof *x);

  clock_gettime(CLOCK_REALTIME, &start);
  PageRank_iterations(dampConst, threshold, n, e, numDangling, &val, col_idx,
    row_ptr, dangling_idx, x);
  clock_gettime(CLOCK_REALTIME, &end);
  accum = (end.tv_sec-start.tv_sec) + 1e-9*(end.tv_nsec-start.tv_nsec);
  printf("PageRank_iterations, time = %lf s\n", accum);

  free(val);
  free(col_idx);
  free(row_ptr);
  free(dangling_idx);
  free(x);
  return 0;
}
