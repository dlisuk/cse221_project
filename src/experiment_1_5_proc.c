#include "basic_experiment.c"

int p2c[2];
int c2p[2];
int pid;
unsigned long v1, v2;

void setup() {

  // parent to child pipe
  pipe(p2c);
  // child to parent pipe
  pipe(c2p);

  // fork processes
  pid = fork();
  if(!pid) { //child reads and returns msgs forever

    char inmsg;
    unsigned long recv_time;

    // for parent to child, close write descriptor
    close(p2c[1]);
    // for child to parent, close read descriptor
    close(c2p[0]);

    while(1) {

      //wait for parent to send msg
      read(p2c[0], &inmsg, 1);
      GET_HIGH(recv_time);
      //printf("msg %s recv at %d\n", inmsg, recv_time);

      //if parent indicates done, quit
      if(inmsg == 'd') {
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
      }

      //else write time of msg reciept
      if(inmsg == '0') {
      	write(c2p[1], (char*)&recv_time, sizeof(unsigned long));
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

  //unsigned long block_time;
  unsigned long recv_time;
  //send message to child
  write(p2c[1], "0", 1);
  //wait for child response
  //block_time = 0;
  int v1 = c2p[0];
  char * v2 = (char*)&recv_time;
  int v3 = sizeof(unsigned long);
  //GET_HIGH(block_time);
  reset();
  read(v1, v2, v3);

  //return block_time;
  return recv_time;
}
