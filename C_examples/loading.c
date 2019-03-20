#include <stdio.h>
#include <unistd.h>

int main() {
  /* Simple loading bar:
   * [.  ]
   * [.. ]
   * [...]
   */
  printf("[   ]"); fflush(stdout); sleep(1);
  for (int t=0; t<2; t++) {
    printf("\b\b\b\b.  ]"); fflush(stdout); sleep(1);
    printf("\b\b\b. ]"); fflush(stdout); sleep(1);
    printf("\b\b.]"); fflush(stdout); sleep(1);
    printf("\b\b\b\b   ]"); fflush(stdout); sleep(1);
  }
  printf("\n");
  return 0;
}
