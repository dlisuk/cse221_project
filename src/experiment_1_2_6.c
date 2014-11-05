#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long inside_time;

void f6(int v1, int v2, int v3, int v4, int v5, int v6) {
  inside_time = ccnt_read();
}

unsigned long measure () {
  unsigned long outside_time = ccnt_read();
  f6(1,2,3,4,5,6);
  return inside_time - outside_time;
}
