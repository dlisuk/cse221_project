/* CPU Experiment 2: Procedure call overhead, four arguments
 * see experiment_1_2_3.c
 */

#include "basic_experiment.c"

void setup() {}
void teardown(){}

unsigned long t;

void f0(int v1, int v2, int v3, int v4) {
  GET_HIGH(t);
}

unsigned long measure () {
  // make sure i, o in cache and TLB
  t=0;
  int v1 = 1;
  int v2 = 2;
  int v3 = 3;
  int v4 = 4;
  RESET;
  f0(v1, v2, v3, v4);
  return t;
}
