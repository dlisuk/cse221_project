#include "basic_experiment.c"

void setup() {}
void teardown(){}

struct timespec inside_time, outside_time;

void f0(int v1, int v2, int v3, int v4, int v5, int v6) {
  GT(inside_time);
}

unsigned long measure () {
  GT(outside_time);
  f0(1,2,3,4,5,6);
  if(inside_time.tv_nsec < outside_time.tv_nsec) {
    inside_time.tv_nsec += 1000000000;
  }
  return inside_time.tv_nsec - outside_time.tv_nsec;
}
