#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "cycles.h"

#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char * buffer;
	posix_memalign((void **)&buffer, 4096, 4096);

	//Open file results file
	FILE * results;

	char datafile[128];
	int trial;
	strcpy(datafile, argv[0]+2); //name of object, without "./" at start
	trial = strlen(datafile);
	datafile[trial-2] = 0; //get rid of ".o"
	strcat(datafile, "_data"); //"experiment_xxx_data"
	results = fopen(datafile, "w");
	fprintf(results, "n\tcount\tmean cycles/byte\tvar cycles/byte\n");

	FILE * test_file_write;
	int    test_file_read;

	//Loop on mem size
	int i, j, k;
	int n = 512;
	unsigned long delta1,delta2;
	int count;
	for (i = 1; i <= 20; i++){
		test_file_write = fopen("tmp", "w");
		for( j = 0; j < n; j ++){
			fprintf(test_file_write, "%c", 1);
		}
		fclose(test_file_write);

		for(j = 0; j< 10; j++){
			test_file_read = open("tmp", O_RDONLY | O_DIRECT | O_SYNC);
			RESET;
			for(k = 0; k < n; k+=4096){
				read(test_file_read, &buffer, 4069);
			}
			GET_LOW(delta1);
			RESET;
			for(k = 0; k < n; k+=4096){
				read(test_file_read, &buffer, 4069);
			}
			GET_LOW(delta2);
			close(test_file_read);
			delta1 *= 64;
			delta2 *= 64;
			fprintf(results, "%d\t%lu\t%lu\n",n,delta1,delta2);
			printf("%d\t%lu\t%lu\n",n,delta1,delta2);
		}
		n *= 2;
	}
}
