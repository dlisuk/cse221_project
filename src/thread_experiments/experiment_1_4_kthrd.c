#include <stdio.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "constants.h"

FILE * dp;
typdef struct task_struct ts;
ts cur_task;
unsigned long p_recv_time, c_recv_time;
int[2] p2c;
int[2] c2p;
char * filename = "experiment_1_4_kthrd_data";
char derp;


int reply_with_time(void *watev) {
  GET_HIGH(c_recv_time);
  write(c2p[1], "0", 1);
  return 0;
}

int exp_init() {

  // initialize pipe
  pipe(p2c);
  pipe(c2p);

  // open data file
  dp = fopen(filename, "w");

  int i;
  for(i = 0; i< MAX_N; ++i) {
    int (*f)(void *) = &reply_with_time;
    void * data =0;
    char * z = "0";
    RESET;
    //ts = kthread_create(f,data,z);
    kthread_create(f,data,z);
    GET_HIGH(p_recv_time);
    read(c2p[0], &derp, 1);
    fprintf(dp, "%ul\n", recv_time);
  }

  return 0;
}

int exp_exit() {
  fclose(dp);
  close(c2p[0]);
  close(c2p[1]);
  close(p2c[0]);
  close(p2c[1]);
}
