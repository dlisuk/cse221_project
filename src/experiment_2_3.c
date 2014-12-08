#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "cycles.h"

int main(int argc, char *argv[]){
	//Open file results file
	FILE * results;
	char datafile[128];
	int trial;
	strcpy(datafile, argv[0]+2); //name of object, without "./" at start
	trial = strlen(datafile);
	datafile[trial-2] = 0; //get rid of ".o"
	strcat(datafile, "_data"); //"experiment_xxx_data"
	results = fopen(datafile, "w");

	int i; 
	int x;
	unsigned long delta;
	int n = 1;
	int count;
	
	char * data;
	int fd = open ("random_file", O_RDONLY);
	struct stat s;
	int status = fstat (fd, & s);
	size_t size = s.st_size;
	data = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

	//Loop on mem size
	double mean_old, mean_new = 0.0;
	double var_old, var_new   = 0.0;
	for (i = 0; i < size; i += 4096*1024 ){
		RESET;
		x += data[i];
		GET_HIGH(delta);
		if( i == 0){
			count = 1;
			mean_old = mean_new = delta;
		}else{
			count ++;
			mean_new = mean_old + (delta - mean_old)/count;
			var_new  = ((count-1)*var_old + (delta - mean_old)*(delta - mean_new))/count;

			mean_old = mean_new;
			var_old  = var_new;
		}
	}
	var_new = sqrt(var_new/count);
	printf("%d\n",x);
	fprintf(results, "%d\t%d\t%g\t%g\n",i,count,mean_new,var_new);
}
