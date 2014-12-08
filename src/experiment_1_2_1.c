#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long t;

void f0(int v1) {
  GET_HIGH(t);
}

unsigned long measure () {
  // make sure i, o in cache and TLB
  t = 0;
  int v1 = 1;
  RESET;
  f0(v1);
  return t;
}
