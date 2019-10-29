#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "week5.h"

void low_triangle_MVM(double **A, double *B, double *y, int N);
void low_triangle_MVM_optimized(double **A, double *B, double *y, int N);

int main(int argc, char* argv[]) {
  if (argc < 2) {
      printf("Usage: ./unroll_and_jam.exe N\n");
      return 1;
  }
  int N = atoi(argv[1]);
  clock_t start1, end1, start2, end2;
  double clocks_to_ms = 0.001/(double) CLOCKS_PER_SEC;
  double **A;
  double *B = malloc(N * sizeof *B);
  double *y1 = calloc(N, sizeof *y1);
  double *y2 = calloc(N, sizeof *y2);
  alloc2D(&A,N,N);
  for (size_t j=0; j<N; j++) {
    B[j] = j*0.5;
    for (size_t i=0; i<=j; i++) {
      A[j][i] = (j+i)*0.3;
    }
  }
  printf("A = \n");
  printmat(A,N,N);
  printf("B = \n");
  printvec(B,N);

  start1 = clock();
  low_triangle_MVM(A, B, y1, N);
  end1 = clock();
  double time1 = (end1-start1)*clocks_to_ms;
  printf("Result normal:\n");
  printvec(y1,N);
  for (size_t j=0; j<N; j++) {
    for (size_t i=0; i<=j; i++) {
      A[j][i] = (j+i)*0.3;
    }
  }
  start2 = clock();
  low_triangle_MVM_optimized(A, B, y2, N);
  end2 = clock();
  double time2 = (end2-start2)*clocks_to_ms;
  printf("Result unroll:\n");
  printvec(y2,N);
  printf("Speedup = %1.2f\n", time1/time2);
  free2D(A);
  free(B);
  free(y1);
  free(y2);
  return 0;
}

void low_triangle_MVM(double **A, double *B, double *y, int N) {
  for (size_t j=0; j<N; j++) {
    for (size_t i=0; i<=j; i++) {
      y[j] += A[j][i]*B[i];
    }
  }
}

void low_triangle_MVM_optimized(double **A, double *B, double *y, int N) {
  int remainder = N%4;

  for (size_t j=0; j<remainder; j++) {
    for (size_t i=0; i<=j; i++) {
      y[j] += A[j][i]*B[i];
    }
  }

  for (size_t j=remainder; j<N; j+=4) {
    for (size_t i=0; i<=j; i++) {
      y[j] += A[j][i]*B[i];
      y[j+1] += A[j+1][i]*B[i];
      y[j+2] += A[j+2][i]*B[i];
      y[j+3] += A[j+3][i]*B[i];
    }
    // last 3 elems not finished:
    y[j+1] += A[j+1][j+1]*B[j+1];
    y[j+2] += A[j+2][j+1]*B[j+1];
    y[j+2] += A[j+2][j+2]*B[j+2];
    y[j+3] += A[j+3][j+1]*B[j+1];
    y[j+3] += A[j+3][j+2]*B[j+2];
    y[j+3] += A[j+3][j+3]*B[j+3];
  }
}
