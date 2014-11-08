//Taken from http://blog.regehr.org/archives/794
//Use the read the instruction counter on rasbery pi
#include <time.h>

/*
struct timespec gettime_now;
static inline unsigned long ccnt_read ()
{
  clock_gettime(CLOCK_REALTIME, &gettime_now);
  return gettime_now.tv_nsec;
}
*/

static inline unsigned ccnt_read() {
  unsigned cc;
  asm volatile ("mrc p15, 0, %0, c15, c12, 1" : "=r"(cc) );
  return cc;
}

unsigned long absdiff(unsigned long t1, unsigned long t2) {

  if(t2 < t1) {
    t2+=1000000000;
  }
  return t2 - t1;

}

#define GT(X) clock_gettime(CLOCK_MONOTONIC, &(X))
