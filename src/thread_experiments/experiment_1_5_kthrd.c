#include <stdio.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "constants.h"

typdef struct task_struct ts;

FILE * dp;
ts cur_task;
unsigned long recv_time;
int[2] p2c;
int[2] c2p;
char * filename = "experiment_1_4_kthrd_data";
char derp;


int reply_with_time(void *watev) {

  while(1) {
    read(p2c[0], &derp, 1);
    GET_HIGH(recv_time);
    if(derp == '0') { // done
      write(c2p[1],"1",1);
      return 0;
    }
    write(c2p[1], "1", 1);
  }

}

int exp_init() {

  // initialize pipe
  pipe(p2c);
  pipe(c2p);

  // open data file
  dp = fopen(filename, "w");

  // create child thread
  ts = kthread_create(&reply_with_time,0,"0");

  int i;
  for(i = 0; i< MAX_N; ++i) {
    RESET;
    write(p2c[1],"1",1);
    read(c2p[0],&derp,1);
    fprintf(dp,"%ul\n",recv_time);
  }

  return 0;
}

int exp_exit() {
  write(p2c[1],"0",1);
  read(c2p[0],&derp,1);
  fclose(dp);
  close(c2p[0]);
  close(c2p[1]);
  close(p2c[0]);
  close(p2c[1]);
}
