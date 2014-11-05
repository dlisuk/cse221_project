#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long inside_time;

void f1(int v1) {
  inside_time = ccnt_read();
}

unsigned long measure () {
  unsigned long outside_time = ccnt_read();
  f1(1);
  return inside_time - outside_time;
}
