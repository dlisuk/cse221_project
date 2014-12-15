/* Memory Experiment 2: RAM Bandwidth
 * In order to measure memory bandwidth,
 * we again need to ensure that reads don't
 * go to the cache. We read 16 ints of
 * data, each 4 memory addresses appart,
 * so that the same two cache lines are not
 * used consecutively. We repeat with writes.
 * we measure the time taken for all of hte
 * 16 reads to complete, and divide by the
 * elapsed time to figure out the bandwidth.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cycles.h"

int main(int argc, char *argv[]){
	double mean_old, mean_new = 0.0;
	double var_old, var_new   = 0.0;
	int * data = (int*)malloc(16777216);
	unsigned int i;
	unsigned long delta;
	int n = 1;
	int count;

	//Open file results file
	FILE * results;
	char datafile[128];
	int trial;
	strcpy(datafile, argv[0]+2); //name of object, without "./" at start
	trial = strlen(datafile);
	datafile[trial-2] = 0; //get rid of ".o"
	strcat(datafile, "_data"); //"experiment_xxx_data"
	results = fopen(datafile, "w");

	//Write test
	RESET;
	for (i = 0; i < 16777216.0*sizeof(char)/sizeof(int); i+=128){
		data[i] = 1;
		data[i+8] = 1;
		data[i+16] = 1;
		data[i+24] = 1;
		data[i+32] = 1;
		data[i+40] = 1;
		data[i+48] = 1;
		data[i+56] = 1;
		data[i+64] = 1;
		data[i+72] = 1;
		data[i+80] = 1;
		data[i+88] = 1;
		data[i+96] = 1;
		data[i+104] = 1;
		data[i+112] = 1;
		data[i+120] = 1;
	}
	GET_HIGH(delta);
	fprintf(results, "write\t%d\t%d\t%f\n", delta, (i+16), (i+16.0)/delta);

	unsigned long x = 0;
	RESET;
	for (i = 0; i < 16777216.0*sizeof(char)/sizeof(int); i+=128){
		x=data[i] ;
		x=data[i+8] ;
		x=data[i+16] ;
		x=data[i+24] ;
		x=data[i+32] ;
		x=data[i+40] ;
		x=data[i+48] ;
		x=data[i+56] ;
		x=data[i+64] ;
		x=data[i+72] ;
		x=data[i+80] ;
		x=data[i+88] ;
		x=data[i+96] ;
		x=data[i+104] ;
		x=data[i+112] ;
		x=data[i+120] ;

	}
	GET_HIGH(delta);
	fprintf(results, "read\t%d\t%d\t%f\t%ul\n", delta, (i+16), (i+16.0)/delta, x);
}
