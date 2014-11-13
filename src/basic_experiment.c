#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
//#include "cycles.c"
#include "cycles.h"

/**
 * make as many variables global as possible
 */

//struct timespec outer_start, outer_end;
unsigned long outer_start, outer_end;
unsigned long delta_int;
double mean_old, mean_new, var_old, var_new, delta;
FILE * results;
int trial;
char datafile[128];

/**
 * Prototype for function to measure, should return the number of clock cycles
 */
//static inline unsigned long execute();
void setup();
unsigned long measure();
void teardown();

/*
int c(const void * p1, const void * p2) {
  unsigned long l1 = *((unsigned long *)p1);
  unsigned long l2 = *((unsigned long *)p2);
  if(l1 < l2) return -1;
  if(l1 > l2) return 1;
  return 0;
}
*/

int main(int argc, char *argv[]){
  reset();
  //mean_old, mean_new = 0.0;
  //var_old, var_new   = 0.0;
  //unsigned long * measurements = (unsigned long *)malloc(MAX_N*sizeof(unsigned long));

  strcpy(datafile, argv[0]+2); //name of object, without "./" at start
  trial = strlen(datafile);
  datafile[trial-2] = 0; //get rid of ".o"
  strcat(datafile, "_data"); //"experiment_xxx_data"
  results = fopen(datafile, "w");
  setup();
  printf("RUNNING MEASURE %d TIMES\n\n", MAX_N);
  for(trial=0; trial < MAX_N; ++trial){

    delta_int = measure();
    if(errno){
      printf("Failed at trial %d\n", trial);
      fclose(results);
      exit(1);
    }
    fprintf(results, "%lu\n",delta_int);
    //measurements[i-1] = delta_int;
    //delta = delta_int;

    //printf("trial:%d\n", i);

    /*
    if( i == 1){
      mean_old = mean_new = delta;
    }else{
      mean_new = mean_old + (delta - mean_old)/i;
      var_new  = ((i-1)*var_old + (delta - mean_old)*(delta - mean_new))/i;

      mean_old = mean_new;
      var_old  = var_new;
    }
    */
  }
  teardown();
  printf("EXPERIMENT COMPLETE\n");
  //fprintf(results, "%d\n", outer_start.tv_nsec);
  //fprintf(results, "%d\n", outer_end.tv_nsec);
  /*
  printf("sorting\n");
  qsort(measurements, MAX_N, sizeof(unsigned long), &c);
  printf("sorted\n");
  var_new = sqrt(var_new/(MAX_N-1));
  //printf("OUTER MEASRUES\n");
  //printf("Total\t%lu\n", outer_end-outer_start );
  //printf("Mean\t%f\n\n", (outer_end-outer_start)/(1.0*MAX_N));

  printf("INNER MEASURES\n");
  printf("MEAN\t%f\nSTD_DEV\t%f\n\n", mean_new, var_new);
  printf("MEDIAN\t%d\n", measurements[MAX_N >> 1]);
  */
}
