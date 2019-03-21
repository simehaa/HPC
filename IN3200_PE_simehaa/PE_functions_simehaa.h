#ifndef PE_FUNCTIONS_SIMEHAA_H
#define PE_FUNCTIONS_SIMEHAA_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // fabs
#include <time.h>
#include <omp.h> // OpenMP

// Function declarations
void read_graph_from_file(char*, int*, int* e, int, int*, double**, int**,
  int**, int**);
void PageRank_iterations(double, double, int, int, int, double**, int*, int*,
  int*, double*, int*, int*, double*);
void top_n_webpages(int, int, double*, double*, int*);
void print_sparse_matrix(double*, int*, int*, int, int);
void swap(int*, int*);
void sort_perm(int*, int*, int, int);
void print_sparse_matrix(double*, int*, int*, int, int);

#endif // PE_FUNCTIONS_SIMEHAA_H
