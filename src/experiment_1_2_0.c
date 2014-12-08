#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long t;

void f0() {
  GET_HIGH(t);
}

unsigned long measure () {
  t = 0;
  RESET;
  f0();
  return t;
}
