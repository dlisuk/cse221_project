#include "basic_experiment.c"
#include "cycles.h"

void setup() {}
void teardown(){}

unsigned long inside_time;

void f0() {
  inside_time = ccnt_read();
}

unsigned long measure () {
  unsigned long outside_time = ccnt_read();
  f0();
  return inside_time - outside_time;
}
