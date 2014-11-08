#include <stdlib.h> 
#include <stdio.h>

#include "cycles.h"

void main(){
	double mean_old, mean_new = 0.0;
	double var_old, var_new   = 0.0;
	int * data = malloc(16777216 * sizeof(int));
	int i, j, k, x;
	unsigned long delta;
	int n = 1;
	int count;
	for (i = 0; i < 16777216; i++){
		data[i] = i;
	}
	//Loop on mem size
	for (i = 1; i <= 24; i++){
		double mean_old, mean_new = 0.0;
		double var_old, var_new   = 0.0;
		for(j = 0; j< 1000; j++){
			for(k = 0; k < n; k+=100){
				reset();
				x = data[k];
				GET_HIGH(delta);
				if( j<5 ){
					//Warm up
				}else if( j == 5 && k == 0){
					count = 1;
					mean_old = mean_new = delta;
				}else{
					mean_new = mean_old + (delta - mean_old)/count;
					var_new  = ((count-1)*var_old + (delta - mean_old)*(delta - mean_new))/count;

					mean_old = mean_new;
					var_old  = var_new;
				}
			}
		}
		printf("%d\t%d\t%g\t%g\n",i,count,mean_new,var_new);
		n *= 2;
	}
}
