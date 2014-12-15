/* CPU Experiment 2: Procedure call overhead, void return
 * measures the overhead of a void return by calling a
 * procedure, resetting the cycle counter, returning,
 * and recording the time elapsed
 */

#include "basic_experiment.c"

void setup() {}
void teardown() {}

unsigned long inside_time, outside_time;

void f0() {
  RESET;
}

unsigned long measure () {
  f0();
  GET_HIGH(outside_time);
  return outside_time;
}
