#include "basic_experiment.c"

void setup() {}
void teardown() {}

struct timespec inside_time, outside_time;

void f0() {
  GT(inside_time);
}

unsigned long measure () {
  f0();
  GT(outside_time);
  if(outside_time.tv_nsec < inside_time.tv_nsec) {
    outside_time.tv_nsec += 1000000000;
  }
  return outside_time.tv_nsec - inside_time.tv_nsec;
}
