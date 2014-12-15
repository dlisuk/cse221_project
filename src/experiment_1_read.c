/* Misc CPU Experiment: pipe read overhead
 * measures the overhead of reading from
 * a pipe by forking a process after 
 * establishing a pair of communication
 * pipes between them; ensuring that the 
 * next child read will not block;
 * resetting the cycle counter; reading
 * from (one of) the pipe; and 
 * recording the elapsed time
 */

#include "basic_experiment.c"

int p2c1[2];
int p2c2[2];
int c2p[2];

void setup() {
  pipe(p2c1);
  pipe(p2c2);
  pipe(c2p);

  if(!fork()) { // child
    // close irrelevant descriptors
    close(p2c1[1]);
    close(p2c2[1]);
    close(c2p[0]);

    unsigned long t;
    int rl;
    int p2c2d;
    char *tptr;
    /*
    char *e;
    e = (char*)malloc(5);
    char e[5];
    e[4] = 0;
    */
    char toss;
    while(1) {
      // read from first descriptor
      read(p2c1[0], &toss, 1);
      if(toss == '1') {
        close(p2c1[0]);
        close(p2c2[0]);
        close(c2p[1]);
        exit(0);
      }

      // time read from second descriptor
      t=0;
      rl = 1;
      toss = 0;
      tptr = &toss;
      p2c2d = p2c2[0];
      RESET;
      read(p2c2d, tptr, rl);
      GET_HIGH(t);

      // write time to third descriptor
      write(c2p[1], (char*)&t, sizeof(unsigned long));

    }
  }

  // parent closes irrelevant descriptors
  close(p2c1[0]);
  close(p2c2[0]);
  close(c2p[1]);

}

void teardown() {

  // tell child to quit
  write(p2c1[1], "1", 1);

  // close irrelevant descriptors
  close(p2c1[1]);
  close(p2c2[1]);
  close(c2p[0]);

}

unsigned long measure () {

  unsigned long recv_time;

  write(p2c1[1], "0", 1);
  write(p2c2[1], "0", 1);
  read(c2p[0], (char*)&recv_time, sizeof(unsigned long));

  return recv_time;

}
