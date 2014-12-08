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
