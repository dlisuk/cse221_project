void small_sort(unsigned long * ularr, len) {

}

unsigned long select(unsigned long * ularr, pos, len) {

  // sort each sub-group of 5
  int num_parts = len/5;
  int last_part = len%5;
  int i;
  for(i = 0; i < num_parts; ++i) {
    small_sort((unsigned long *)(ularr+5*i),5);
  }
  if(last_part) {
    small_sort((unsigned long *)(ularr+5*i),last_part);
  }

  // find median of medians (MM)
  int num_meds = num_parts;
  if(last_part) ++num_meds;
  unsigned long * med_arr = (unsigned long *)malloc(num_meds * sizeof(unsigned long));
  for(i=0; i < num_parts; ++i) {
    med_arr[i] = ularr[5*i+2];
  }
  if(last_part) {
    med_arr[i] = ularr[5*i+(last_part >> 1)];
  }
  unsigned mm = select(med_arr, num_meds >> 1, num_meds);

  // elements less than MM go at start;
  // elements greater than MM go at end
  int fptr = 0, lptr = len, eqptr = 0;
  unsigned long * ularr_copy = (unsigned long *)malloc(len*sizeof(unsigned long));
  //unsigned long * med_eqs = (unsigned long *)malloc(len*sizeof(unsigned long));
  for(i=0; i<len; ++i) {
    unsigned long q = ularr[i];
    if(q < mm) {
      ularr_copy[fptr++] = q;
    } else if(ularr[i] > mm) {
      ularr_copy[--lptr] = q;
    } /* else {
      med_eqs[eqptr++] = q;
    }
    */
  }
  // fill gap space with mm
  int fptr_cpy = fptr;
  while(fptr_cpy < lptr) {
    ularr_copy[fptr_cpy++]=mm;
  }

  // if MM at pos, return MM
  // elif MM < pos, find pos in >MM
  // else MM > pos, find pos in <MM
  if(fptr < pos && lptr > pos) {
    return mm;
  } else if
}
