#include "basic_experiment.c"

static unsigned long execute(struct timespec *gettime_now){
  return ccnt_read(gettime_now);
}
