#ifndef PE_FUNCTIONS_SIMEHAA_H
#define PE_FUNCTIONS_SIMEHAA_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*void swap(int*, int*);
void sort_perm(int*, int*, int, int);
void print_sparse_matrix(double*, int*, int*, int, int);
void read_graph_from_file(char*);*/

void swap(int *a, int *b) {
  int t=*a; *a=*b; *b=t;
}

void sort_perm(int *arr, int *perm, int beg, int end) {
  if (end > beg + 1) {
    int piv = arr[perm[beg]], l = beg + 1, r = end;
    while (l < r) {
      if (arr[perm[l]] <= piv)
        l++;
      else
        swap(&perm[l], &perm[--r]);
    }
    swap(&perm[--l], &perm[beg]);
    sort_perm(arr, perm, beg, l);
    sort_perm(arr, perm, r, end);
  }
}

void print_sparse_matrix(double* val, int* col_idx, int* row_ptr, int nodes, int edges) {
  // Print of val array
  printf("\nval:");
  printf("\n[%f, ", val[0]);
  for (int i=1; i<edges-1; i++) {
    printf("%f, ", val[i]);
  }
  printf("%f]\n", val[edges-1]);

  // Print of col_idx array
  printf("\ncol_idx:");
  printf("\n[%i, ", col_idx[0]);
  for (int i=1; i<edges-1; i++) {
    printf("%i, ", col_idx[i]);
  }
  printf("%i]\n", col_idx[edges-1]);

  // Print of row_ptr array
  printf("\nrow_ptr:");
  printf("\n[%i, ",row_ptr[0]);
  for (int i=1; i<nodes-1; i++) {
    printf("%i, ", row_ptr[i]);
  }
  printf("%i]\n\n",row_ptr[nodes-1]);
}


void read_graph_from_file(char* filename, int maxEdges) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(filename, "r");
  if (fp == NULL)
    exit(0);

  int nodes, edges;
  // Read first 4 lines, extract #nodes and #edges
  read = getline(&line, &len, fp);
  read = getline(&line, &len, fp);
  read = getline(&line, &len, fp);
  sscanf(line, "%*s %*s %i %*s %i", &nodes, &edges);
  read = getline(&line, &len, fp);
  edges = maxEdges;

  int *FromNodeId = malloc(edges * sizeof *FromNodeId);
  int *ToNodeId = malloc(edges * sizeof *ToNodeId);
  int *number_outgoing = calloc(nodes, sizeof *number_outgoing);
  int *number_incoming = calloc(nodes, sizeof *number_incoming);
  int *perm = malloc(edges * sizeof *perm);

  // Extract data
  for (int i=0; i<edges; i++) {
    read = getline(&line, &len, fp);
    sscanf(line, "%i %i", &FromNodeId[i], &ToNodeId[i]);
    number_outgoing[FromNodeId[i]]++; // L[i]
    number_incoming[ToNodeId[i]]++; // K[i]
    perm[i] = i;
  }
  /* Matrix element:
   * if K[j] != 0 and i != j,
   *     a_ij = 1/L[j],
   * else:
   *     a_ij = 0
   * Matrix will be set up as a sparse matrix according to CRS.
   */

  nodes = FromNodeId[edges-1]; // According to maxedges
  fclose(fp);
  free(line);

  // Count dangling webpages
  double col_vals[edges];
  int num_dangling = 0;
  for (int i=0; i<nodes; i++) {
    if (number_outgoing[i] == 0)
      num_dangling++;
  }

  // Find arrays: col_vals, dangling_idx, row_ptr
  int *row_ptr = malloc(nodes * sizeof *row_ptr);
  int dangling_idx[num_dangling]; num_dangling = 0;
  int sum = 0;
  for (int i=0; i<nodes; i++) {
    if (number_outgoing[i] != 0) {
      col_vals[i] = 1.0/number_outgoing[i];
      row_ptr[i] = sum;
    } else {
      dangling_idx[num_dangling] = i; num_dangling++;
    }
    sum += number_incoming[i];
  }

  // Sort perm correctly by ToNodeId from least to greatest node
  // Each node-chunk in ToNodeId sorted by FromNodeId
  sort_perm(ToNodeId, perm, 0, edges);
  int beg=0, end=0;
  for (int node=0; node<nodes; node++) {
    end += number_incoming[node];
    sort_perm(FromNodeId, perm, beg, end);
    beg = end;
  }

  // Set up arrays: val, col_idx
  double *val = malloc(edges * sizeof *val);
  int *col_idx = malloc(edges * sizeof *col_idx);
  int elems, idx=0;
  for (int i=0; i<edges; i++) {
    col_idx[i] = FromNodeId[perm[i]];
    val[i] = col_vals[col_idx[i]];
  }

  // print_sparse_matrix(val, col_idx, row_ptr, nodes, edges);

  free(FromNodeId);
  free(ToNodeId);
  free(number_outgoing);
  free(number_incoming);
  free(val);
  free(col_idx);
  free(row_ptr);
  free(perm);
}

/*double* PageRank_iterations(double damping_const, double threshold) {
  return
}

void top_n_webpages(int n) {
  //
}*/


#endif // PE_FUNCTIONS_SIMEHAA_H
