#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long measure() {
  struct timespec t0, t1;
  GT(t0);GT(t1);
  if(t1.tv_nsec < t0.tv_nsec) {
    t1.tv_nsec+=1000000000;
  }
  return t1.tv_nsec - t0.tv_nsec;
}
