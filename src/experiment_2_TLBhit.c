/* Misc Memory experiment: TLB hit measurement
 * measures the time to service a TLB hit by
 * repeatedly reading the same variable and
 * measuring the time taken to do this
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
  // also e
  e = 0;

  asm volatile ("ldr	r4, .L18");
  RESET;
  asm volatile ("ldr	r4, [r4]");
  GET_HIGH(e);
  return e;
}
