#include <stdio.h>
#include <sys/mman.h>

int main () {

	printf("%d\n", getpagesize());

	return 0;
}
