#include "basic_experiment.c"
// #include "cycles.c"

void setup() {}
void teardown(){}

unsigned long measure() {
  unsigned long m0 = ccnt_read();
  unsigned long m1 = ccnt_read();
  return m1-m0; 
}
