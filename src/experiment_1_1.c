#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long measure() {
  unsigned long t0 = 0, t1 = 0;
  GET_HIGH(t0);
  GET_HIGH(t1);
  return absdiff(t0, t1);
}
