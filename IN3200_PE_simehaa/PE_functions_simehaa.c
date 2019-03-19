#include <stdio.h>
#include <stdlib.h>

void print_sparse_matrix(double* val, int* col_idx, int* row_ptr) {
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


void read_graph_from_file(char* filename) {
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

  int *FromNodeId = malloc(edges * sizeof *FromNodeId);
  int *ToNodeId = malloc(edges * sizeof *ToNodeId);
  int *number_outgoing = calloc(nodes, sizeof *number_outgoing);
  int *number_incoming = calloc(nodes, sizeof *number_incoming);

  // Extract data
  for (int i=0; i<edges; i++) {
    read = getline(&line, &len, fp);
    sscanf(line, "%i %i", &FromNodeId[i], &ToNodeId[i]);
    number_outgoing[FromNodeId[i]]++;
    number_incoming[ToNodeId[i]]++;
  }
  fclose(fp);
  free(line);

  // Find column values (constant along each column)
  double col_vals[edges];
  double val = malloc(edges * sizeof *val);
  int col_idx = malloc(edges * sizeof *col_idx);
  int row_ptr[ = malloc(nodes * sizeof *row_ptr);
  int dangling_idx[nodes];

  int ctr = 0;
  for (int i=0; i<nodes; i++) {
    if (number_outgoing[i] != 0) {
      col_vals[i] = 1.0/number_outgoing[i];
    } else {
      dangling_idx[ctr] = i; ctr++;
    }
  }

  // Find row_ptr + indices of dangling webpages
  int sum = 0;
  for (int i=0; i<nodes; i++) {
    if (number_outgoing[i] != 0) {
      row_ptr[i] = sum;
    }
    sum += number_incoming[i];
  }

  // HARD WAY (but it works)
  // Find col_idx and val
  ctr = 0;
  for (int i=0; i<nodes; i++) {
    for (int j=0; j<edges; j++) { // Many uneccessary long loops here
      if (ToNodeId[j] == i) {
        val[ctr] = col_vals[FromNodeId[j]];
        col_idx[ctr] = FromNodeId[j];
        ctr++;
      }
    }
  }

  // Attempt easy way
  /*ctr = 0;
  for (int i=0; i<edges; i++) {
    col_vals[FromNodeId[j]]
    for (int j=0; j<edges; j++) {
      if (ToNodeId[j] == i) {
        val[ctr] = ;
        col_idx[ctr] = FromNodeId[j];
        ctr++;
      }
    }
  }*/
  print_sparse_matrix(val, col_idx, row_ptr);
  
  free(FromNodeId);
  free(ToNodeId);
  free(number_outgoing);
  free(number_incoming);
  free(val);
  free(col_idx);
  free(row_ptr);
}

/*double* PageRank_iterations(double damping_const, double threshold) {
  return
}

void top_n_webpages(int n) {
  //
}*/
