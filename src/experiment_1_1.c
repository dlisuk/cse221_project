#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long measure() {
  //unsigned long t0 = 0, t1 = 0;
  //GET_HIGH(t0);
  unsigned long t1;
  t1 = 0;
  RESET;
  GET_HIGH(t1);
  return t1;
}
