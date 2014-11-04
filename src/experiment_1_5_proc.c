#include "basic_experiment.c"
#include "cycles.c"

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

    char inmsg[5];
    inmsg[4]='\0';
    unsigned long recv_time;

    // for parent to child, close write descriptor
    close(p2c[1]);
    // for child to parent, close read descriptor
    close(c2p[0]);

    while(1) {

      //wait for parent to send msg
      read(p2c[0], inmsg, 4);
      recv_time = ccnt_read();
      //printf("msg %s recv at %d\n", inmsg, recv_time);

      //if parent indicates done, quit
      if(!strcmp(inmsg, "done")) {
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
      }

      //else write time of msg reciept
      if(!strcmp(inmsg, "8==D")) {
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
  write(p2c[1], "done", 4);
  close(c2p[0]);
  close(p2c[1]);
}

unsigned long measure() {

  do {
    unsigned long block_time, recv_time;
    //send message to child
    write(p2c[1], "8==D", 4);
    //wait for child response
    block_time = ccnt_read();
    read(c2p[0], (char*)&recv_time, sizeof(unsigned long));
  } while(recv_time < block_time);

  /*
  v1 = block_time;
  v2 = recv_time;
  // */

  return recv_time - block_time;
}
