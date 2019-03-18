#ifndef PAGERANK_H
#define PAGERANK_H
#include <stdio.h>
#include <stdlib.h>

void read_graph_from_file(char* filename) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(filename, "r");
  if (fp == NULL)
      exit(1);

  int nodes, edges;
  // Read first 4 lines, extract #nodes and #edges
  read = getline(&line, &len, fp);
  read = getline(&line, &len, fp);
  read = getline(&line, &len, fp);
  sscanf(line, "%*s %*s %i %*s %i", &nodes, &edges);
  read = getline(&line, &len, fp);

  int *FromNodeId = malloc(edges * sizeof *FromNodeId);
  int *ToNodeId = malloc(edges * sizeof *ToNodeId);
  int *incoming = calloc(nodes, sizeof *incoming);
  // Extract data
  for (int i=0; i<edges; i++) {
    read = getline(&line, &len, fp);
    sscanf(line, "%i %i", &FromNodeId[i], &ToNodeId[i]);
    incoming[ToNodeId[i]]++;
  }

  // Find column values (constant along each column)
  double *col_vals = malloc(nodes * sizeof *col_vals);
  for (int i=0; i<nodes; i++) {
    col_vals[i] = 1.0/incoming[i];
    printf("%f\n", col_vals[i]);
  }
  free(FromNodeId);
  free(ToNodeId);
  free(incoming);
  free(col_vals);
  /*
  double *val = malloc(edges * sizeof *val);
  int *col = malloc(edges * sizeof *col);
  int *row = malloc(nodes * sizeof *row);
  free(val);
  free(col);
  free(row);*/
  fclose(fp);
  if (line)
     free(line);
  /*
  int nodes, edges;
  FILE *FilePtr;
  FilePtr = fopen(filename, "r");
  if (FilePtr == NULL) {
    exit(1);
  }
  fclose(FilePtr);

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  read = getline(&line, &len, FilePtr);
  printf("%ld", read);
  read = getline(&line, &len, FilePtr);
  fscanf(FilePtr,"%i %i", &nodes, &edges);
  getline(&line, &len, FilePtr);
  printf("%i %i \n", nodes, edges);
  free(line);

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
  exit(EXIT_SUCCESS);*/
}

/*double* PageRank_iterations(double damping_const, double threshold) {
  return
}

void top_n_webpages(int n) {
  //
}*/

#endif // PAGERANK_H
