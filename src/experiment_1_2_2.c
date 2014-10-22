#include "basic_experiment.c"

unsigned function_2(unsigned x_1, unsigned 2){
  return ccnt_read();
}

static inline unsigned execute(void){
  return function_1(1, 2);
}
