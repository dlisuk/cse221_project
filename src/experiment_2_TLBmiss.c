#include "basic_experiment.c"

char tlb[(TLB_ENTRIES+2)*PAGE_SIZE];
char * dyn = 0;
char * start_page;
int alttag;
unsigned long start, end;

void setup() {

  // malloc dyn
  dyn = (char*) malloc(1);

  // caculate altpage
  alttag = ((int)dyn ^ 32) & (PAGE_SIZE - 32);

  // find first page boundary in tlb
  start_page = (char *)(((int)tlb + PAGE_SIZE) & (~(PAGE_SIZE - 1)) );

  // put dyn in cache
  *dyn = 0;

}
void teardown() {

  free(dyn);

}

unsigned long measure() {

  // where is dyn?
  *dyn = 0;

  // flush tlb, keep dyn in cache
  char * s = start_page + alttag;
  int i;
  for(i = 0; i<TLB_ENTRIES; ++i) {
    *s = *s;
    s+=PAGE_SIZE;
  }

  // make sure start, end in cache
  start = 0;
  end = 0;
  // load pointer to dyn data
  asm volatile("ldr	r4, .L22");   // address of dyn
  asm volatile("ldr	r4, [r4]");   // data in dyn, pointer
  GET_HIGH(start);
  asm volatile("ldr	r4, [r4]");   // read *dyn
  GET_HIGH(end);

  return absdiff(start,end);

}
