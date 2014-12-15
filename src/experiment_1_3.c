/* CPU Experiment 3: System call overhead
 * measures the overhead of a system call
 * by placing its arguments into local
 * variables, resetting the cycle counter,
 * making the system call (passing the parameters
 * via the local variables), and measuring
 * the elapsed time
 */

#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include "basic_experiment.c"

void setup() {}
void teardown() {}

unsigned long measure(){
  //int rc;
  unsigned long t;
  t=0;
  long v1 = SYS_getcpu;
  RESET;
  syscall(v1);
  GET_HIGH(t);
  errno = 0;
  return t;
}
