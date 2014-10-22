#include "basic_experiment.c"

unsigned function_1(unsigned x_1){
  return ccnt_read();
}

static inline unsigned execute(void){
  return function_1(1);
}
