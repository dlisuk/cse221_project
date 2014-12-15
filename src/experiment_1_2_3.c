/* CPU Experiment 2: Procedure call overhead, 3 arguments
 * measures the overhead of a procedure call with three
 * arguments by storing the argument values in local variables
 * , resetting the cycle counter, calling the procedure
 * and passing the arguments via the local variables (for 
 * standardization), and within the function, storing the
 * elapsed time in a global variable 
 */

#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long t;

void f0(int v1, int v2, int v3) {
  GET_HIGH(t);
}

unsigned long measure () {
  // make sure i, o in cache and TLB
  t=0;
  int v1 = 1;
  int v2 = 2;
  int v3 = 3;
  RESET;
  f0(v1, v2, v3);
  return t;
}
