#ifndef PE_FUNCTIONS_SIMEHAA_H
#define PE_FUNCTIONS_SIMEHAA_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*void swap(int*, int*);
void sort_perm(int*, int*, int, int);
void print_sparse_matrix(double*, int*, int*, int, int);
void read_graph_from_file(char*);*/

void print_sparse_matrix(double*, int*, int*, int, int);

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

void sort_perm_double(double *arr, int *perm, int beg, int end) {
  if (end > beg + 1) {
    double piv = arr[perm[beg]];
    int l = beg + 1, r = end;
    while (l < r) {
      if (arr[perm[l]] <= piv)
        l++;
      else
        swap(&perm[l], &perm[--r]);
    }
    swap(&perm[--l], &perm[beg]);
    sort_perm_double(arr, perm, beg, l);
    sort_perm_double(arr, perm, r, end);
  }
}

void read_graph_from_file(char* filename, int* n, int* e, int maxEdges, int*
    numDangling, double** val, int** col_idx, int** row_ptr, int** dangling_idx)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(filename, "r");
  if (fp == NULL)
    exit(0);

  // Read first 4 lines, extract #nodes and #edges
  int edges, nodes;
  read = getline(&line, &len, fp);
  read = getline(&line, &len, fp);
  read = getline(&line, &len, fp);
  sscanf(line, "%*s %*s %i %*s %i", &nodes, &edges);
  read = getline(&line, &len, fp);
  if (edges > maxEdges)
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

  nodes = FromNodeId[edges-1] + 1; // According to maxedges
  (*n) = nodes;
  (*e) = edges;
  fclose(fp);
  free(line);

  // Count dangling webpages
  for (int i=0; i<nodes; i++) {
    if (number_outgoing[i] == 0)
      (*numDangling)++;
  }

  // save indices of dangling nodes
  int idx = 0;
  *dangling_idx = malloc((*numDangling) * sizeof *dangling_idx);
  for (int i=0; i<nodes; i++) {
    if (number_outgoing[i] == 0) {
      (*dangling_idx)[idx] = i; idx++;
    }
  }

  // Find arrays: col_vals, dangling_idx, row_ptr
  double col_vals[nodes];
  *row_ptr = malloc((nodes+1) * sizeof *row_ptr);
  (*row_ptr)[nodes] = edges;
  int sum = 0;
  for (int i=0; i<nodes; i++) {
    if (number_incoming[i]) {
      col_vals[i] = 1.0/number_outgoing[i];
      (*row_ptr)[i] = sum;
    } else {
      col_vals[i] = 0;
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
  *val = malloc(edges * sizeof *val);
  *col_idx = malloc(edges * sizeof *col_idx);
  for (int i=0; i<edges; i++) {
    (*col_idx)[i] = FromNodeId[perm[i]];
    (*val)[i] = col_vals[(*col_idx)[i]];
  }

  // print_sparse_matrix(val, col_idx, row_ptr, nodes, edges);

  free(FromNodeId);
  free(ToNodeId);
  free(number_outgoing);
  free(number_incoming);
  free(perm);
}

void PageRank_iterations(double dampConst, double threshold, int nodes, int edges,
    int numDangling, double** val, int* col_idx, int* row_ptr, int* dangling_idx,
    double* x, int* iter, int* maxiter, double* diff)
{
  // factors and constants
  double nth = 1.0 / (double) nodes;
  double factor2 = dampConst*nth;
  double factor1 = nth - factor2;
  int idx = 0;
  double maxdiff = 1.0, tempdiff;
  double *temp = malloc(edges * sizeof *temp);
  // initialize x
  for (int i=0; i<nodes; i++) x[i] = nth;
  // update val: d * val
  for (int i=0; i<edges; i++) (*val)[i] *= dampConst;

  // PageRank algorithm
  while (maxdiff > threshold && (*iter) < (*maxiter)) {
    double W = 0;
    for (int i=0; i<numDangling; i++) W += x[dangling_idx[i]];
    W *= factor2;
    W += factor1;
    // Matrix vector multiplication
    idx = 0;
    for (int i=0; i<nodes; i++) {
      temp[i] = W;
      for (int j=row_ptr[i]; j<row_ptr[i+1]; j++) {
        temp[i] += (*val)[idx] * x[col_idx[j]]; idx++;
      }
    }
    maxdiff = temp[0] - x[0];
    for (int i=0; i<nodes; i++) {
      tempdiff = fabs(temp[i] - x[i]);
      if (tempdiff > maxdiff)
        maxdiff = tempdiff;
      x[i] = temp[i];
    }
    (*iter)++;
  }
  (*diff) = maxdiff;
  free(temp);
}

void top_n_webpages(int nTopWebpages, int nodes, double* x, int* perm) {
  for (int i=0; i<nodes; i++) perm[i] = i;
  sort_perm_double(x, perm, 0, nodes);
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


#endif // PE_FUNCTIONS_SIMEHAA_H
