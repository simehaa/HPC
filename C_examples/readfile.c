#include <stdio.h>
#include <stdlib.h>

int main(int narg, char *argv[]) {
  FILE *binFilePtr, *txtFilePtr;
  if (narg < 2) {
    printf("Enter cmd line argument for length of array");
    printf("Usage example: $ ./a.out 10000");
    exit(0);
  }
  int n = atoi(argv[1]);
  double *data = malloc(n * sizeof *data);

  // textfile write
  txtFilePtr = fopen("data.txt", "w");
  for (int i=0; i<n; i++) fprintf(txtFilePtr, "%lf\n", data[i]);
  fclose(txtFilePtr);

  // textfile read
  txtFilePtr = fopen("data.txt", "r");
  double *fromfile = malloc(n * sizeof *fromfile);
  for (int i = 0; i < n; i ++) fscanf(txtFilePtr,"%lf", &fromfile[i]);
  fclose(txtFilePtr);
  free(fromfile);

  // binfile write
  binFilePtr = fopen("data.bin", "wb");
  fwrite(data, sizeof(double), n, binFilePtr);
  fclose(binFilePtr);

  // binfile read
  fromfile = malloc(n * sizeof *fromfile);
  binFilePtr = fopen("data.bin", "rb");
  fread(fromfile, sizeof(double), n, binFilePtr);
  fclose(binFilePtr);
  free(fromfile);
}
