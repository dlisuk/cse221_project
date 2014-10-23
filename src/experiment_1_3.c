#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include "basic_experiment.c"

static inline unsigned long execute(){
  int rc;
  rc = syscall(SYS_chmod, "/etc/passwd", 0444);
  return rc;
}
