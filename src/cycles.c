//Taken from http://blog.regehr.org/archives/794
//Use the read the instruction counter on rasbery pi
#include <time.h>

inline unsigned long ccnt_read (struct timespec *gettime_now)
{
  clock_gettime(CLOCK_REALTIME, gettime_now);
  return gettime_now->tv_nsec;
}
