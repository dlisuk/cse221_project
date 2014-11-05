#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include "basic_experiment.c"

void setup() {}
void teardown() {}

unsigned long measure(){
  int rc;
  unsigned long s = ccnt_read();
  rc = syscall(SYS_chmod, "/etc/passwd", 0444);
  unsigned long e = ccnt_read();
  
  return e-s;
}
