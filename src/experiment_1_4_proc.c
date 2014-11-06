#include "basic_experiment.c"
#include <unistd.h>
#include <errno.h>

void setup(){}
void teardown(){}

unsigned long measure() {

    printf("measuring: ");

    int pfd[2];
    unsigned long ctime; //child  post-fork
    struct timespec t_start_ts, t_end_ts;


    pipe(pfd); //create communication pipe
    printf("pipe created ");
    // execute experiment
    GT(t_start_ts);
    if (vfork()) { //parent
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
        read(pfd[0], (char*)&ctime, sizeof(unsigned long));
        //close write pipe
        close(pfd[1]);

        // close read pipe
        close(pfd[0]);

    } else { // child
        printf("child created ");
        GT(t_end_ts);
        //close read pipe
        close(pfd[0]);

        //send time
        write(pfd[1], (char*)&(t_end_ts.tv_nsec), sizeof(unsigned long));

        //close pipe and exit
        close(pfd[1]);
        printf("child finished ");
        exit(0);
    }

    printf("complete\n");

    return absdiff(t_start_ts.tv_nsec, ctime);


}
