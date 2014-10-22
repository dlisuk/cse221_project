#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "cycles.c"

/**
 * Prototype for function to measure, should return the number of clock cycles
 */
static inline unsigned execute(void);

int main(void){
  double mean_old = mean_new = 0.0;
  double var_old = var_new   = 0.0;

  printf("RUNNING MEASURE %d TIMES\n\n", MAX_N);
  unsigned outer_start = ccnt_read();
  for(unsigned i=1; i <= MAX_N; i++){
    unsigned t_start = ccnt_read();
    execute();
    unsigned t_end = ccnt_read();

    double delta = t_end - t_start; 

    if( i == 1){
      mean_old = mean_new = delta;
    }else{
      mean_new = mean_old + (delta - mean_old)/i;
      var_new  = var_old + (delta - mean_old)*(delta - mean_new);

      mean_old = mean_new;
      var_old  = var_new;
    }
  }
  unsigned outer_end = ccnt_read();

  var_new = sqrt(var_new/(N-1));
  printf("OUTER MEASRUES\n");
  printf("MEAN\t%f\n\n", (outer_end - outer_start)/(1.0*MAX_N));

  printf("INNER MEASURES\n");
  printf("MEAN\t%f\nSTD_DEV\t%f\n\n", mean_new, var_new);

  }
}
