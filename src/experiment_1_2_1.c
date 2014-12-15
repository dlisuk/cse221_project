/* CPU Experiment 2: Procedure call overhead, 1 argument
 * measures the overhead of a procedure call with one 
 * argument by resetting the timer, calling the procedure,
 * and within the function, storing the elapsed time in
 * a global variable
 */

#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long t;

void f0(int v1) {
  GET_HIGH(t);
}

unsigned long measure () {
  // make sure i, o in cache and TLB
  t = 0;
  int v1 = 1;
  RESET;
  f0(v1);
  return t;
}
