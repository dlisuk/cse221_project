#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <string.h>

#include "cycles.h"

int main(int argc, char *argv[]){
	double mean_old, mean_new = 0.0;
	double var_old, var_new   = 0.0;
	char * data = malloc(16777216 * sizeof(char));
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
	reset();
	for (i = 0; i < 16777216 - 15; i+=16){
		data[i] = 1;
		data[i+1] = 1;
		data[i+2] = 1;
		data[i+3] = 1;
		data[i+4] = 1;
		data[i+5] = 1;
		data[i+6] = 1;
		data[i+7] = 1;
		data[i+8] = 1;
		data[i+9] = 1;
		data[i+10] = 1;
		data[i+11] = 1;
		data[i+12] = 1;
		data[i+13] = 1;
		data[i+14] = 1;
		data[i+15] = 1;
	}
	GET_HIGH(delta);
	fprintf(results, "write\t%d\t%d\t%f\n", delta, (i+16), (i+16.0)/delta);
	
	unsigned long x = 0;
	reset();
	for (i = 0; i < 16777216 - 15; i+=16){
		x = data[i];
		x = data[i+1];
		x = data[i+2];
		x = data[i+3];
		x = data[i+4];
		x = data[i+5];
		x = data[i+6];
		x = data[i+7];
		x = data[i+8];
		x = data[i+9];
		x = data[i+10];
		x = data[i+11];
		x = data[i+12];
		x = data[i+13];
		x = data[i+14];
		x = data[i+15];
	}
	GET_HIGH(delta);
	fprintf(results, "read\t%d\t%d\t%f\t%ul\n", delta, (i+16), (i+16.0)/delta, x);
}
