#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include "basic_experiment.c"

void setup() {}
void teardown() {}

unsigned long measure(){
  //int rc;
  unsigned long s, e;
  s=0;
  e=0;
  long v1 = SYS_chmod;
  char * v2 = "/etc/passwd";
  int v3 = 0444;
  GET_LOW(s);
  //rc = syscall(SYS_chmod, "/etc/passwd", 0444);
  syscall(v1, v2, v3);
  GET_LOW(e);
  return absdiff(s, e);
}
