#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include "basic_experiment.c"

void setup() {}
void teardown() {}

unsigned long measure(){
  int rc;
  struct timespec s, e;
  GT(s);
  rc = syscall(SYS_chmod, "/etc/passwd", 0444);
  GT(e);
  return absdiff(s.tv_nsec, e.tv_nsec);
}
