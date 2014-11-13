#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long i, o;

void f0() {
  GET_HIGH(i);
}

unsigned long measure () {
  // make sure i, o in cache and TLB
  i=0;
  o=0;
  GET_HIGH(o);
  f0();
  return absdiff(o, i);
}