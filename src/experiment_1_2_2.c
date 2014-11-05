#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long inside_time;

void f2(int v1, int v2) {
  inside_time = ccnt_read();
}

unsigned long measure () {
  unsigned long outside_time = ccnt_read();
  f2(1,2);
  return inside_time - outside_time;
}
