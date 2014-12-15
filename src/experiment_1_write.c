/* Misc CPU Experiment: write call overhead
 * measures the overhead of writing to 
 * a pipe by forking a process after
 * establishing pipes for the child
 * and parent to communicate by; ensuring
 * that the next write by the child will not
 * block; reset the cycle counter; writing
 * to the pipe; and then measuring hte
 * time elapsed
 */

#include "basic_experiment.c"

int p2c[2];
int c2p[2];

void setup() {

  pipe(p2c);
  pipe(c2p);

  if(!fork()) { // child
    // close irrelevant descriptors
    close(p2c[1]);
    close(c2p[0]);

    char toss;
    while(1) {
      read(p2c[0], &toss, 1);
      if(toss == '1') {
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
      }
      //write(c2p[1], "0", 1);
    }
  }

  // close irrelevant descriptors
  close(p2c[0]);
  close(c2p[1]);

}
void teardown() {

  // tell child to quit
  write(p2c[1], "1", 1);
  close(p2c[1]);
  close(c2p[0]);

}

unsigned long measure () {

  unsigned long wtime;
  char toss;

  int d = p2c[1];
  char * m = "0";
  int rl = 1;
  RESET;
  write(d, m, rl);
  GET_HIGH(wtime);
  //read(c2p[0], &toss, 1);

  return wtime;

}
