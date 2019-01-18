#include <stdio.h>

int main() {
  FILE *fp;
  char *mode = "r";
  fp = fopen ("in3200/set1/filename.txt","r");
  if (fp == NULL)
  {
    printf("Error in reading file.");
    exit(1);
  }
  char line[12]; // 11 characters + NULL character

  return 0;
}
