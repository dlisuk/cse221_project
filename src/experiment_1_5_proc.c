/* CPU Experiment 5: Context swtich overhead
 * measures the overhead of a context switch by
 * forking a process after establishing a 
 * pair of communication pipes, which block
 * when one attempts to read them if nobody
 * has written anything to it; resetting the
 * cycle counter; sending a message from the 
 * parent to the child; and measuring the 
 * elapsed time at which the child receives
 * the message
 */

#include "basic_experiment.c"

int p2c[2];
int c2p[2];
//int pid;
unsigned long v1, v2;

void setup() {

  // parent to child pipe
  pipe(p2c);
  // child to parent pipe
  pipe(c2p);

  // fork processes
  if(!fork()) { //child reads and returns msgs forever

    char inmsg;

    // for parent to child, close write descriptor
    close(p2c[1]);
    // for child to parent, close read descriptor
    close(c2p[0]);

    while(1) {

      //wait for parent to send msg
      read(p2c[0], &inmsg, 1);

      //if parent indicates done, quit
      if(inmsg == 'd') {
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
      }

      //else write time of msg reciept
      if(inmsg == '0') {
  	RESET;
      	write(c2p[1], "0", 1);
      }
    }
  } else { //parent closes appropriate descriptors

    // for parent to child, close read descriptor
    close(p2c[0]);
    // for child to parent, close write descriptor
    close(c2p[1]);
  }
}

void teardown() {
  write(p2c[1], "d", 1);
  close(c2p[0]);
  close(p2c[1]);
}

unsigned long measure() {
  char inmsg;
  unsigned long recv_time;

  write(p2c[1], "0", 1);
  read(c2p[0], &inmsg, 1);
  GET_HIGH(recv_time);

  return recv_time;
}
