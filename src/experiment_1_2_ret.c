#include "basic_experiment.c"

void setup() {}
void teardown() {}

unsigned long inside_time;

void f0() {
  inside_time = ccnt_read();
}

unsigned long measure () {
  f0();
  unsigned long outside_time = ccnt_read();  
  return outside_time - inside_time;
}
