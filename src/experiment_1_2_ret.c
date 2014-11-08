#include "basic_experiment.c"

void setup() {}
void teardown() {}

unsigned long inside_time, outside_time;

void f0() {
  inside_time = 0;
  outside_time = 0;
  GET_LOW(inside_time);
}

unsigned long measure () {
  f0();
  GET_LOW(outside_time);
  return absdiff(inside_time, outside_time);
}
