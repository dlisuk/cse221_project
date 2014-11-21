#include "basic_experiment.c"

void setup() {}
void teardown() {}

unsigned long outside_time;

int f0() {
  int rv;
  outside_time = 0;
  rv = 0;
  RESET;
  return rv;
}

unsigned long measure () {
  f0();
  GET_HIGH(outside_time);
  return outside_time;
}
