#include <stdlib.h>
#include <stdio.h>

#include "PE_functions_simehaa.h"

int main(int argc, char **argv) {
  // ./pagerank.exe filename dampConst convThreshold nTopWebpages
  if (argc < 5) {
    printf("Usage error:\n");
    printf("$ ./pagerank.exe filename dampConst convThreshold nTopWebpages\n");
    exit(0);
  }

  char* filename = argv[1]; //"8-webpages.txt";
  double dampConst = atoi(argv[2]);
  double convThreshold = atoi(argv[3]);
  int nTopWebpages = atoi(argv[4]);
  printf("%s\n", filename);
  printf("%f\n", dampConst);
  printf("%f\n", convThreshold);
  printf("%i\n", nTopWebpages);
  read_graph_from_file(filename);
  return 0;
}
