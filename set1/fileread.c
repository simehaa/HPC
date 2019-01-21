#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE *fp;
  fp = fopen ("temp.dat","r");
  if (fp == NULL)
  {
    printf("Error in reading file.\n");
    exit(1);
  }

  char line[12];
  char time[6], maxtime[6], mintime[6];
  float temp, maxtemp=-100, mintemp=100;

  while (!feof(fp))
  {
    fscanf(fp, "%s %f", time, &temp);
    if (temp > maxtemp)
    {
      maxtemp = temp;
      strncpy(maxtime, time, 6);
    }
    if (temp < mintemp)
    {
      mintemp = temp;
      strncpy(mintime, time, 6);
    }
  }
  printf("maxtemp = %.2f, at time %s\n", maxtemp, maxtime);
  printf("mintemp = %.2f, at time %s\n", mintemp, mintime);

  fclose(fp);
  return 0;
}
