#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "constants.h"
#include "cycles.c"

int child_wins = 0;

unsigned long measure() {

    int pfd[2];
    pipe(pfd); //create communication pipe
    // execute experiment
    unsigned long t_start;
    unsigned long t_end; //parent post-fork
    unsigned long ctime; //child  post-fork
    t_start = ccnt_read();
    if (fork()) { //parent
        t_end = ccnt_read();
        //read(pfd[0], (char*)&ctime, sizeof(unsigned long));
        //close write pipe
        close(pfd[1]);
    } else { // child
        t_end = ccnt_read();

        //close read pipe
        close(pfd[0]);

        //send time
        write(pfd[1], (char*)&t_end, sizeof(unsigned long));

        //close pipe and exit
        close(pfd[1]);
        exit(0);
    }
    read(pfd[0], (char*)&ctime, sizeof(unsigned long));
    // close read pipe
    close(pfd[0]);
    // if child ran first, t_end should be child start
    if(ctime < t_end) {
        ++child_wins;
        t_end = ctime;
    }

    if(t_end < t_start) {
        t_end+=1000000000;
    }

    return t_end - t_start;

}

int main(void){
  double mean_old, mean_new, mean_old_noout, mean_new_noout = 0.0;
  double var_old, var_new, var_old_noout, var_new_noout  = 0.0;
  unsigned long outlier_max = 1000000;

  unsigned long outer_start = ccnt_read();
  int i;
  int o_count = 0;
  for(i=1; i <= MAX_N; i++){

    double delta = measure();

    if( i == 1){
      mean_old = mean_new = delta;
    }else{
      mean_new = mean_old + (delta - mean_old)/i;
      var_new  = ((i-1)*var_old + (delta - mean_old)*(delta - mean_new))/i;

      mean_old = mean_new;
      var_old  = var_new;
    }
    //if(i%100000 == 0) {
    //if(delta > outlier_max) {
    //    printf("delta:%17f\n", delta);
    //    printf("mean: %17f\n", mean_new);
    //} else {
    if(delta < outlier_max) {
        ++o_count;
        if(o_count == 1) {
          mean_new_noout = mean_old_noout = delta;
        } else {
          mean_new_noout = mean_old_noout + (delta - mean_old_noout)/o_count;
          var_new_noout = ((o_count-1)*var_old_noout + (delta - mean_old_noout) * (delta - mean_new_noout))/o_count;
          mean_old_noout = mean_new_noout;
          var_old_noout = var_new_noout;
        }

    }



  }
  unsigned long outer_end = ccnt_read();

  var_new = sqrt(var_new/(MAX_N-1));
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

  printf("CHILD WINS:%d\n", child_wins);
}
