#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  clock_t start, end;
  double time;
  double buffer[1000000];
  for (long j=0; j<1000000; j++) {
    buffer[j] = j*0.1;
  }

  // Write and read binary
  FILE *wp;
  FILE *fp;
  start = clock();
  wp = fopen("test.txt","w");
  fwrite(buffer,sizeof(buffer),1,wp);
  fclose(wp);
  end = clock();
  time = (end - start)/((double)CLOCKS_PER_SEC);
  printf("ASCII write time = %lf\n", time);

  start = clock();
  fp = fopen("test.txt","r");
  fread(buffer,sizeof(buffer),1,fp);
  fclose(fp);
  end = clock();
  time = (end - start)/((double)CLOCKS_PER_SEC);
  printf("ASCII read time = %lf\n", time);

  return 0;
}
