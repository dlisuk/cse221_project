#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "constants.h"
#include "cycles.h"

#define PROG_ARG 0
#define TRIAL_ARG 1
#define TIME_ARG 2
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
//char[5] time;
//char[5] trial;

/*
int check_zeros(unsigned long c) {

  char * cc = (char*)(&c);

  int i;
  for(i = 0; i < sizeof(unsigned long); ++i) {
    if(cc[i] == 0) {
      return 0;
    }
  }

  return 1;

}
*/

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

  // get start time
  GET_HIGH(et);

  //printf("argc: %d\n", argc);

  if(argc == 1) {
    // first run; start first trial
    //printf("beginning first run\n");

    newargs[PROG_ARG] = execname;
    // allocate memory for time
    newargs[TIME_ARG] = (char*)malloc(33);
    newargs[TIME_ARG][32] = 0;
    //printf("time argument allocated\n");
    newargs[TRIAL_ARG] = "1";

    // allocate null argument
    newargs[NULL_ARG] = (char*)malloc(1);
    newargs[NULL_ARG][0]=0;

    // create/overwrite data file
    dp = fopen(datafile, "w");
    fclose(dp);

    // exec first trial
    GET_HIGH(et);
    *(unsigned long *)newargs[TIME_ARG] = et;
    execv(execname, newargs);
  } else {

    // extract trial number from args
    trial = strtol(argv[TRIAL_ARG], err_ptr, 10);
    printf("executing trial %d\n", trial);

    // if time is 4 bytes, write time difference to file
    if(strlen(argv[TIME_ARG]) == 4){
      dp = fopen(datafile, "a");
      et -= *(unsigned long*)argv[TIME_ARG];
      fprintf(dp, "%d\n", et);
      fclose(dp);
    }

  }

  // check trial; exit if 1000000
  if(trial >= MAX_N) {
    exit(0);
  }

  // increment trial, get time, and and continue
  newargs[PROG_ARG] = execname;
  newargs[NULL_ARG] = (char*)malloc(1);
  newargs[NULL_ARG][0] = 0;
  if(strlen(argv[TIME_ARG]) == 4) {
    newargs[TRIAL_ARG] = (char*)malloc(33);
    ltostr(trial+1, newargs[TRIAL_ARG]);
  } else {
    newargs[TRIAL_ARG] = argv[TRIAL_ARG];
  }

  newargs[TIME_ARG] = (char*)malloc(sizeof(unsigned long)+1);
  newargs[TIME_ARG][sizeof(unsigned long)] = 0;
  GET_HIGH(et);
  *(unsigned long *)newargs[TIME_ARG] = et;
  execv(execname, newargs);

  if(errno) {
    printf("unable to execute trial %d\n", trial);
  }

  return 0;

}
