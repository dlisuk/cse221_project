#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long inside_time;

void f7(int v1, int v2, int v3, int v4, int v5, int v6, int v7) {
  inside_time = ccnt_read();
}

unsigned long measure () {
  unsigned long outside_time = ccnt_read();
  f7(1,2,3,4,5,6,7);
  return inside_time - outside_time;
}
