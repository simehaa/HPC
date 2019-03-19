#include <stdlib.h>
#include <stdio.h>

#include "PE_functions_simehaa.h"

int main(int argc, char **argv) {
  if (argc < 5) {
    printf("Usage error:\n");
    printf("$ ./pagerank.exe filename dampConst convThreshold nTopWebpages\n");
    exit(0);
  }
  char* filename = argv[1];
  double dampConst = atoi(argv[2]);
  double convThreshold = atoi(argv[3]);
  int nTopWebpages = atoi(argv[4]);

  struct timespec start, end;

  clock_gettime(CLOCK_REALTIME, &start);
  read_graph_from_file(filename, 900000); // Segmentation fault for MaxEdges > 927 000.
  clock_gettime(CLOCK_REALTIME, &end);

  double accum = (end.tv_sec-start.tv_sec) + 1e-9*(end.tv_nsec-start.tv_nsec);
  printf("read_graph_from_file, time = %lf s\n", accum);

  return 0;
}
