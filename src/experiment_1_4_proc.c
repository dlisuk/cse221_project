#include "basic_experiment.c"
#include <unistd.h>
#include <errno.h>

void setup(){}
void teardown(){}

unsigned long measure() {

    printf("measuring: ");

    int pfd[2];
    unsigned long start, end;

    pipe(pfd); //create communication pipe
    printf("pipe created ");
    // execute experiment
    start = 0;
    GET_LOW(start);
    if (vfork()) { //parent
        /*
        printf("parent resumed ");
        if(errno) {
          printf("Error: ");
          if(errno == EAGAIN) {
            printf("process limit reached\n");
          } else if (errno == ENOMEM) {
            printf("no memory\n");
          }
          errno = 0;
          return 0;
        }
        */
        read(pfd[0], (char*)&end, sizeof(unsigned long));
        //close write pipe
        close(pfd[1]);

        // close read pipe
        close(pfd[0]);

    } else { // child
        GET_LOW(end);
        printf("child created ");
        //close read pipe
        close(pfd[0]);

        //send time
        write(pfd[1], (char*)&end, sizeof(unsigned long));

        //close pipe and exit
        close(pfd[1]);
        printf("child finished ");
        exit(0);
    }

    //printf("complete\n");

    return absdiff(start, end);


}
