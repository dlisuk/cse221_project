/* CPU Experiment 2: Procedure call overhead, word return
 * measures the overhead of returning a word value from
 * a procedure by calling the procedure, placing the return
 * value in a word variable, resetting the cycle counter,
 * returning the value via the word variable, and
 * measuring the time elapsed
 */

#include "basic_experiment.c"

void setup() {}
void teardown() {}

unsigned long outside_time;

int f0() {
  int rv;
  outside_time = 0;
  rv = 0;
  RESET;
  return rv;
}

unsigned long measure () {
  f0();
  GET_HIGH(outside_time);
  return outside_time;
}
