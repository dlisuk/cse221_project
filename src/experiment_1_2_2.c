/* CPU Experiment 2: procedure call overhead, two arguments
 * measures the overhead of a call to a procedure with two
 * arguments by resetting the timer, placing the arguments in
 * local variables, calling the procedure and passing the 
 * arguments through the local variables (for standardization)
 * and within the function, storing the elapsed time in a global
 * variable
 */

#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long t;

void f0(int v1, int v2) {
  GET_HIGH(t);
}

unsigned long measure () {
  // make sure i, o in cache and TLB
  t=0;
  int v1 = 1;
  int v2 = 2;
  RESET;
  f0(v1, v2);
  return t;
}
