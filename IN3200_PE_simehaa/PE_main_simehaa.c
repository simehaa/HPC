#include "PE_functions_simehaa.h"

int main(int argc, char **argv) {
  if (argc < 5) {
    printf("\nUsage error:\n");
    printf("$ ./pagerank.exe filename dampConst threshold nTopWebpages\n");
    exit(0);
  }
  char* filename = argv[1];
  double dampConst = atof(argv[2]);
  double threshold = atof(argv[3]);
  int nTopWebpages = atoi(argv[4]);
  if (dampConst < 0 || dampConst > 1) {
    printf("\nError: \n  Damping Constant (cmd line argument 3)\n");
    printf("  should be: 0 < d < 1.\n");
    exit(0);
  }
  int n = 0, e = 0;
  int maxEdges = 900000; // unspecified if 0,
  int numDangling = 0;
  int iter = 0, maxiter = 1000;
  double diff;
  double* val = NULL;
  int* col_idx = NULL;
  int* row_ptr = NULL;
  int* dangling_idx = NULL;
  double time_read, time_pagerank, time_topn;
  struct timespec start, end;

  // Read file
  clock_gettime(CLOCK_REALTIME, &start);
  read_graph_from_file(filename, &n, &e, maxEdges, &numDangling, &val, &col_idx,
                       &row_ptr, &dangling_idx);
  clock_gettime(CLOCK_REALTIME, &end);
  time_read = (end.tv_sec-start.tv_sec) + 1e-9*(end.tv_nsec-start.tv_nsec);

  // Information print
  printf("Information:\n");
  printf("  Filename (input data)   = %s\n", filename);
  printf("  Nodes (no. of webpages) = %i\n", n);
  printf("  Edges (no. of links)    = %i \n", e);
  printf("  Damping Constant        = %1.3f\n", dampConst);
  printf("  Convergence threshold   = %1.2e\n\n", threshold);

  // Pagerank algorithm
  double *x = malloc(n * sizeof *x);
  clock_gettime(CLOCK_REALTIME, &start);
  PageRank_iterations(dampConst, threshold, n, e, numDangling, &val, col_idx,
                      row_ptr, dangling_idx, x, &iter, &maxiter, &diff);
  clock_gettime(CLOCK_REALTIME, &end);
  time_pagerank = (end.tv_sec-start.tv_sec) + 1e-9*(end.tv_nsec-start.tv_nsec);

  // Pagerank results
  printf("\nPagerank algorithm results:\n");
  if (iter >= maxiter) {
    printf("  Max iterations %i: reached\n", iter);
    printf("  max diff: |x[k] - x[k-1]| = %f\n", diff);
  } else {
    printf("  Threshold of %1.2e reached,\n", threshold);
    printf("  Iterations: %i\n\n", iter);
  }

  // Timing print
  printf("\nTiming results:\n");
  printf("  Function:              Time [s]:\n");
  printf("  read_graph_from_file   %1.5f\n", time_read);
  printf("  PageRank_iterations    %1.5f\n", time_pagerank);

  // Find and print top n webpages
  int* perm = malloc(n * sizeof *perm);
  clock_gettime(CLOCK_REALTIME, &start);
  top_n_webpages(nTopWebpages, n, x, perm);
  clock_gettime(CLOCK_REALTIME, &end);
  time_topn = (end.tv_sec-start.tv_sec) + 1e-9*(end.tv_nsec-start.tv_nsec);
  printf("  top_n_webpages         %1.5f\n\n", time_topn);

  // Print top n webpages
  printf("\nTop %i webpages:\n", nTopWebpages);
  printf("  Rank:  Index:  Score:\n");
  int ctr=1;
  for (int i=n-1; i>=n-nTopWebpages; i--) {
    printf("  %3i.  %7i  %1.5f\n", ctr++, perm[i], x[perm[i]]);
  }

  // Free allocations
  free(val);
  free(col_idx);
  free(row_ptr);
  free(dangling_idx);
  free(x);
  free(perm);
  return 0;
}
