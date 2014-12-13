#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "cycles.h"

#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>

#include <time.h>

#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){
	srand(time(NULL));

	char * buffer;
	posix_memalign((void **)&buffer, 4096, 2*4096);

	//Open file results file
	FILE * results;

	char datafile[128];
	int trial;
	strcpy(datafile, argv[0]+2); //name of object, without "./" at start
	trial = strlen(datafile);
	datafile[trial-2] = 0; //get rid of ".o"
	strcat(datafile, "_data"); //"experiment_xxx_data"
	results = fopen(datafile, "w");
	FILE * test_file_write;
	int    test_file_read;

	//Loop on mem size
	int pid[512];
	int i, j, k;
	int n_x = 512;
	unsigned long delta1[100],deltabuf;
	int count;
	int ind;
	for( i = 1; i < 32; i*=2){
		for(j = 0; j < i; j++){
			pid[j] = fork();
			if(pid[j] == 0){
				srand(time(NULL) * getpid());
				while(1){
					ind = rand()%1024;
					sprintf(datafile,"./test_files/%d",ind);
					test_file_read = open(datafile, O_RDONLY | O_DIRECT | O_SYNC );
					for(k = 0; k < 65104; k+=4096){
						read(test_file_read, buffer, 4096);
					}
					close(test_file_read);
				}
			}
			printf("%d:%d, ", j, pid[j]);
		}
		printf("\n");
		count = 0;
		for( j = 0; j < 1024; j ++){
			sprintf(datafile,"./test_files/%d",j);
			test_file_read = open(datafile, O_RDONLY | O_DIRECT | O_SYNC );
			for(k = 0; k < 65104; k+=4096){
				RESET;
				read(test_file_read, buffer, 4096);
				GET_HIGH(deltabuf);
				if(count > 100){
					ind = rand()%count;
				}else{
					ind = count;
				}
				if(ind < 100){
					delta1[ind] = deltabuf;
				}
				count ++;
			}
			close(test_file_read);
		}
		for(j = 0; j < 100; j++){
			fprintf(results,"%d\t%lu\n", i, delta1[j]);
			printf("%d\t%lu\n", i, delta1[j]);
		}
		for(j = 0; j < i; j++){
			kill( pid[j], SIGKILL);
		}
	}
}
