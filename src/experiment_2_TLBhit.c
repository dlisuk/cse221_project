/*
 * Experiment: read L1 cache
 */

#include "basic_experiment.c"

//int k, v;
int v;
unsigned long s, e;

void setup() {
  // put a global variable in L1 cache
  v = 0;
}
void teardown() {}

unsigned long measure() {

  // where is v?
  v = 0;

  //return absdiff(s, e);
  asm volatile ("ldr	r4, .L17");
  GET_LOW(s);
  asm volatile ("ldr	r4, [r4]");
  GET_LOW(e);
  return absdiff(s,e);
}
