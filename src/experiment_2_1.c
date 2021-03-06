/* Memory Experiment 1: RAM access time
 * In order to measure ram access time,
 * we need to make sure our reads don't go
 * to cache. To do this, we saturate the
 * cache, and then read continuously
 * increasing addresses which are
 * separated by the length of the cache line,
 * so that we don't read from cache. The
 * time for each read is measured.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <string.h>

#include "cycles.h"

int main(int argc, char *argv[]){
	double mean_old, mean_new = 0.0;
	double var_old, var_new   = 0.0;
	int * data = malloc(16777248 * sizeof(int));
	data = data + 32 - (((unsigned int)data) % 32);
	printf("%d\n", ((unsigned int)data) % 32);
	int i, j, k;
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

	for (i = 0; i < 16777216; i++){
		data[i] = i;
	}
	//Loop on mem size
	register int x=0;
	for (i = 1; i <= 20; i++){
		double mean_old, mean_new = 0.0;
		double var_old, var_new   = 0.0;
		for(j = 0; j< 100; j++){
			for(k = 0; k < n; k+=32){
				RESET;
				x  = data[k];
				GET_HIGH(delta);
				//Do useful work outside the timed region
				data[k] = x;
				if( j<5 ){
					//Warm up
				}else if( j == 5 && k == 0){
					count = 1;
					mean_old = mean_new = delta;
				}else{
					if(delta > 10*mean_old){
					}else{
						count ++;
						mean_new = mean_old + (delta - mean_old)/count;
						var_new  = ((count-1)*var_old + (delta - mean_old)*(delta - mean_new))/count;

						mean_old = mean_new;
						var_old  = var_new;
					}
				}
			}
		}
		var_new = sqrt(var_new/count);
		fprintf(results, "%d\t%d\t%g\t%g\n",i,count,mean_new,var_new);
		n *= 2;
	}
}
