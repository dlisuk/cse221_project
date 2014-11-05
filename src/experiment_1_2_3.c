#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long inside_time;

void f3(int v1, int v2, int v3) {
  inside_time = ccnt_read();
}

unsigned long measure () {
  unsigned long outside_time = ccnt_read();
  f3(1,2,3);
  return inside_time - outside_time;
}
