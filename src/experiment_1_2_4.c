#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long inside_time;

void f4(int v1, int v2, int v3, int v4) {
  inside_time = ccnt_read();
}

unsigned long measure () {
  unsigned long outside_time = ccnt_read();
  f4(1,2,3,4);
  return inside_time - outside_time;
}
