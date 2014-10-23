#include <stdio.h>
#include "cycles.c"

/** A test file showing how cycle reading works */

int main(void){
  long int ans;

  int i;
  for( i = 0; i < 1000; i ++){
    ans = ccnt_read();
    printf("%d\n", ans);
  }
}
