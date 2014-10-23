#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "constants.h"
#include "cycles.c"

int p2c[2];
int c2p[2];
int pid;
unsigned long v1, v2;

void setup() {

  // parent to child pipe
  pipe(p2c);
  // child to parent pipe
  pipe(c2p);

  // fork processes
  pid = fork();
  if(!pid) { //child reads and returns msgs forever

    char inmsg[5];
    inmsg[4]='\0';
    unsigned long recv_time;

    // for parent to child, close write descriptor
    close(p2c[1]);
    // for child to parent, close read descriptor
    close(c2p[0]);

    while(1) {

      //wait for parent to send msg
      read(p2c[0], inmsg, 4);
      recv_time = ccnt_read();
      //printf("msg %s recv at %d\n", inmsg, recv_time);

      //if parent indicates done, quit
      if(!strcmp(inmsg, "done")) {
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
      }

      //else write time of msg reciept
      if(!strcmp(inmsg, "8==D")) {
      	write(c2p[1], (char*)&recv_time, sizeof(unsigned long));
      }
    }
  } else { //parent closes appropriate descriptors

    // for parent to child, close read descriptor
    close(p2c[0]);
    // for child to parent, close write descriptor
    close(c2p[1]);
  }
}

void teardown() {
  write(p2c[1], "done", 4);
  close(c2p[0]);
  close(p2c[1]);
}

unsigned long measure() {
  unsigned long send_time = ccnt_read();
  unsigned long recv_time;
  //send message to child
  write(p2c[1], "8==D", 4);
  //wait for child response
  read(c2p[0], (char*)&recv_time, sizeof(unsigned long));

  //printf("msg rcv at %d\n",recv_time);

  if(recv_time < send_time) {
    recv_time += 1000000000;
  }

  v1 = send_time;
  v2 = recv_time;

  return recv_time - send_time;
}

int main(void){
  double mean_old, mean_new, mean_old_noout, mean_new_noout = 0.0;
  double var_old, var_new, var_old_noout, var_new_noout  = 0.0;
  unsigned long outlier_max = 100000;

  setup();

  unsigned long outer_start = ccnt_read();
  int i;
  int o_count = 0;
  for(i=1; i <= MAX_N; i++){

    double delta = measure();

    if( i == 1){
      mean_old = mean_new = delta;
    }else{
      mean_new = mean_old + (delta - mean_old)/i;
      var_new  = var_old + (delta - mean_old)*(delta - mean_new);

      mean_old = mean_new;
      var_old  = var_new;
    }

    //periodic printouts

    if(i%10000 == 0) {
      printf("sent: %d\n", v1);
      printf("recv: %d\n", v2);
      printf("delta:%f\n", delta);
      printf("mean: %f\n", mean_new);
    }
    // */


    if(delta < outlier_max) {
        ++o_count;
        if(o_count == 1) {
          mean_new_noout = mean_old_noout = delta;
        } else {
          mean_new_noout = mean_old_noout + (delta - mean_old_noout)/o_count;
          var_new_noout = var_old_noout + (delta - mean_old_noout) * (delta - mean_new_noout);
          mean_old_noout = mean_new_noout;
          var_old_noout = var_new_noout;
        }

    }
    // */



  }
  unsigned long outer_end = ccnt_read();

  teardown();

  var_new = sqrt(var_new/(MAX_N-1));

  printf("\n");
  printf("OUTER MEASRUES\n");
  printf("Total\t%lu\n", outer_end-outer_start );
  printf("ITERATIONS:%d\n", MAX_N);
  printf("Mean\t%f\n\n", (outer_end-outer_start)/(1.0*MAX_N));

  printf("INNER MEASURES\n");
  printf("MEAN:%f\nSTD_DEV:%f\n\n", mean_new, var_new);


  printf("WITHOUT OUTLIERS\n");
  printf("OUTLIER CUTOFF:%d\n", outlier_max);
  printf("INLIERS:%d\n",o_count);
  printf("MEAN:%f\nSTD_DEV:%f\n\n", mean_new_noout, var_new_noout);
  // */
}
