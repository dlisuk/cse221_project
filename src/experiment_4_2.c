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
	int i, j, k;
	int n = 512;
	unsigned long delta1[100],deltabuf;
	int count;
	int ind;
	for (i = 1; i <= 20; i++){
		test_file_write = fopen("tmp", "w");
		for( j = 0; j < n; j ++){
			fprintf(test_file_write, "%c", 1);
		}
		fclose(test_file_write);

		for(j = 0; j< 5; j++){
			test_file_read = open("tmp", O_RDONLY | O_DIRECT | O_SYNC);
			count = 0;
			for(k = 0; k < n; k+=4096){
				RESET;
				read(test_file_read, buffer, 4096);
				GET_HIGH(deltabuf);
				if(count > 0){
					ind = rand()%count;
				} else {
					ind = 0;
				}
				if(ind < 100){
					delta1[ind] = deltabuf;
				}
				count ++;
			}
			close(test_file_read);

			for( k = 0; k < 100 && k < count; k++){
				fprintf(results, "seq\t%d\t%lu\n",n,delta1[k]);
				printf("seq\t%d\t%lu\n",n,delta1[k]);
			}

			count = n/4096;
			if(count >= 16){
				test_file_read = open("tmp", O_RDONLY | O_DIRECT | O_SYNC);
				for(k = -10; k < 100; k++){
					ind = (rand()%count)*4096;
					RESET;
					lseek(test_file_read, ind, SEEK_SET);
					read(test_file_read, buffer, 4096);
					GET_HIGH(deltabuf);
					if(k>=0){
						fprintf(results, "rand\t%d\t%lu\t%d\n",n,deltabuf,ind);
						printf("rand\t%d\t%lu\t%d\n",n,deltabuf,ind);
					}
				}
				close(test_file_read);
				for(k = -10; k < 100; k++){
					test_file_read = open("tmp", O_RDONLY | O_DIRECT | O_SYNC);
					ind = (rand()%count)*4096;
					RESET;
					lseek(test_file_read, ind, SEEK_SET);
					read(test_file_read, buffer, 4096);
					GET_HIGH(deltabuf);
					close(test_file_read);
					if(k>=0){
						fprintf(results, "open\t%d\t%lu\t%d\n",n,deltabuf,ind);
						printf("open\t%d\t%lu\t%d\n",n,deltabuf,ind);
					}
				}
			}
		}
		n*=2;
	}
}
