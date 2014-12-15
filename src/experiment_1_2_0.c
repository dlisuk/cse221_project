/* CPU Experiment: procedure call overhead, no arguments
 * measures the overhead of a procedure call with no 
 * arguments by resetting the timer, calling the function, 
 * and within the function, storing the elapsed time in a
 * global variable
 */

#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long t;

void f0() {
  GET_HIGH(t);
}

unsigned long measure () {
  t = 0;
  RESET;
  f0();
  return t;
}
