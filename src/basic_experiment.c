#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "cycles.c"

/**
 * Prototype for function to measure, should return the number of clock cycles
 */
static inline unsigned long execute();

int main(void){
  double mean_old, mean_new = 0.0;
  double var_old, var_new   = 0.0;

  printf("RUNNING MEASURE %d TIMES\n\n", MAX_N);
  unsigned long outer_start = ccnt_read();
  int i;
  for(i=1; i <= MAX_N; i++){
    unsigned long t_start = ccnt_read();
    execute();
    unsigned long t_end = ccnt_read();

    if(t_end < t_start) {
        t_end+=1000000000;
    }
    double delta = t_end - t_start; 

    if( i == 1){
      mean_old = mean_new = delta;
    }else{
      mean_new = mean_old + (delta - mean_old)/i;
      var_new  = ((i-1)*var_old + (delta - mean_old)*(delta - mean_new))/i;

      mean_old = mean_new;
      var_old  = var_new;
    }
  }
  unsigned long outer_end = ccnt_read();

  var_new = sqrt(var_new/(MAX_N-1));
  printf("OUTER MEASRUES\n");
  printf("Total\t%lu\n", outer_end-outer_start );
  printf("Mean\t%f\n\n", (outer_end-outer_start)/(1.0*MAX_N));

  printf("INNER MEASURES\n");
  printf("MEAN\t%f\nSTD_DEV\t%f\n\n", mean_new, var_new);

}
