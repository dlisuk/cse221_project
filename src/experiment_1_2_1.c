#include "basic_experiment.c"

unsigned function(unsigned x_1){
  return x_1;
}

static inline unsigned long execute(struct timespec *gettime_now){
  return function(1);
}
