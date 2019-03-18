#ifndef PAGERANK_H
#define PAGERANK_H
#include <stdio.h>
#include <stdlib.h>

void read_graph_from_file(char* filename) {
  int nodes, edges;
  // double *data = malloc(n * sizeof *data);
  FILE *FilePtr;
  char *line = NULL;
  size_t len = 0;
  FilePtr = fopen(filename, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  getline(&line, &len, FilePtr);
  getline(&line, &len, FilePtr);
  fscanf(FilePtr,"%i %i", &nodes, &edges);
  getline(&line, &len, FilePtr);

  int *data = malloc(2*edges * sizeof *data); // 34 long
  int FromNodeId, ToNodeId;
  for (int i=0; i<edges; i++) {
    fscanf(FilePtr,"%i %i", &FromNodeId, &ToNodeId);
    data[i] = FromNodeId;
    data[i+1] = ToNodeId;
  }
  fclose(FilePtr);
  free(line);
  free(data);
  exit(EXIT_SUCCESS);
}

double* PageRank_iterations(double damping_const, double threshold) {

}

void top_n_webpages(int n) {
  //
}

#endif // PAGERANK_H
