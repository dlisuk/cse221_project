#include "cycles.h"
#include <stdio.h>

int main() {
        int i;
        unsigned long value_l = 0;
        unsigned long value_h = 0;

	reset();
        for(i = 1; i < 10; i++){
                GET_LOW(value_l);
                GET_HIGH(value_h);
                printf("%d\t%lu\t%lu\n",i,value_h, value_l);
        }
        return 0;
}

