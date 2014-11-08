#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long i, o;

void f0(int v1) {
  GET_LOW(i);
}

unsigned long measure () {
  // make sure i, o in cache and TLB
  i=0;
  o=0;
  int v1 = 1;
  GET_LOW(o);
  f0(v1);
  return absdiff(o, i);
}
