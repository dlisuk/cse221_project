#include <stdio.h>
#include "cycles.c"

/** A test file showing how cycle reading works */

int main(void){
  struct timespec gettime_now;
  long int ans;

  int i;
  for( i = 0; i < 1000; i ++){
    ans = ccnt_read(&gettime_now);
    printf("%d\n", ans);
  }
}
