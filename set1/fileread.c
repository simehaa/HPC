#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp;
  char *mode = "r";
  fp = fopen ("temp.dat","r");
  if (fp == NULL)
  {
    printf("Error in reading file.\n");
    exit(1);
  }

  char* time;
  double temp;
  fscanf(fp, "%s", time);
  fscanf(fp, "%le", &temp);
  printf("%s", *time);
  fclose(fp);
  return 0;
}
