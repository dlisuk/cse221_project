/* CPU Experiment 4: Process creation overhead
 * measures hte overhead of process creation 
 * by resetting the cycle counter, calling exec,
 * and immediately measuring the elapsed time in the
 * execced process
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "constants.h"
#include "cycles.h"

#define PROG_ARG 0
#define TRIAL_ARG 1
//#define TIME_ARG 2
#define NULL_ARG 3

FILE * dp;
unsigned long et;
int trial;
char * newargs[4];
char * datafile = "experiment_1_4_proc_exec_data";
char * execname = "experiment_1_4_proc_exec.o";
char * err_ptr;
char newtrial[33];
char newtime[33];

void ltostr(long i, char * buf) {

  if(i == 0) {
    buf[0] = '0';
    buf[1] = '\0';
    return;
  }

  int len = 0;
  while(i) {
    buf[len++] = '0' + i % 10;
    i /= 10;
  }
  buf[len] = 0;

  char * b2 = (char*)malloc(len+1);
  b2[len] = 0;
  int j = 0;
  while(len) {
    b2[--len] = buf[j++];
  }

  strcpy(buf, b2);

}

int main(int argc, char *argv[]) {
  GET_HIGH(et);
  int trial = 0;

  if(argc > 1) {
    // extract trial number from args
    trial = strtol(argv[TRIAL_ARG], 0, 10);

    // if time is 4 bytes, write time difference to file
    dp = fopen(datafile, "a");
    fprintf(dp, "%d\t%lu\n", trial, et);
    fflush(dp);
    fclose(dp);
  }else{
    dp = fopen(datafile, "w");
    fprintf(dp, "");
    fflush(dp);
    fclose(dp);
  }
  // check trial
  if(trial >= 100) {
    exit(0);
  }

  newargs[PROG_ARG] = execname;
  newargs[NULL_ARG] = (char*)malloc(1);
  newargs[NULL_ARG][0] = 0;
  newargs[TRIAL_ARG] = (char*)malloc(33);
  ltostr(trial+1, newargs[TRIAL_ARG]);
  
  // run next trial
  RESET;
  execv(execname, newargs);
  
  if(errno) {
    printf("unable to execute trial %d\n", trial);
  }
  return 0;
}
