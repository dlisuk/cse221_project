#include "basic_experiment.c"
#include <unistd.h>
#include <errno.h>

void setup(){}
void teardown(){}

unsigned long measure() {


    int pfd[2];
    unsigned long start, end;

    pipe(pfd); //create communication pipe
    // execute experiment
    start = 0;
    GET_HIGH(start);
    if (vfork()) { //parent
        if(errno) {
          printf("Error: ");
          if(errno == EAGAIN) {
            printf("process limit reached\n");
          } else if (errno == ENOMEM) {
            printf("no memory\n");
          }
          return 0;
        }
        read(pfd[0], (char*)&end, sizeof(unsigned long));
        //close write pipe
        close(pfd[1]);

        // close read pipe
        close(pfd[0]);

    } else { // child
        GET_HIGH(end);
        //close read pipe
        close(pfd[0]);

        //send time
        write(pfd[1], (char*)&end, sizeof(unsigned long));

        //close pipe and exit
        close(pfd[1]);
        exit(0);
    }


    return absdiff(start, end);


}
