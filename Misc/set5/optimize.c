void foo (int N, double **mat, double **s, int *v) {
  double *val = malloc(256 * sizeof *val);
  double *vtab = malloc(N * sizeof *vtab);
  for (i=0; i<256; i++) {
    val[i] = -cos(2.0*i);
  }
  for (i=0; i<N; i++) {
    vtab[i] = abs(v[i]%256);
  }
  for (int j=0; j<N; j++) {
    val = -cos(2.0*(v[j]%256));
    for (int i=0; i<N; i++) {
      mat[i][j] = s[i][j]*val;
    }
  }
  free(val);
  free(vtab);
}
