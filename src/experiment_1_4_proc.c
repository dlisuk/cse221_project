#include "basic_experiment.c"

void setup(){}
void teardown(){}

unsigned long measure() {

    do {
        int pfd[2];
        pipe(pfd); //create communication pipe
        // execute experiment
        unsigned long t_start;
        unsigned long t_end; //parent post-fork
        unsigned long ctime; //child  post-fork
        t_start = ccnt_read();
        if (fork()) { //parent
    	    t_end = ccnt_read();
    	    read(pfd[0], (char*)&ctime, sizeof(unsigned long));
    	    //close write pipe
    	    close(pfd[1]);
    	} else { // child
    	    t_end = ccnt_read();
	
            //close read pipe
            close(pfd[0]);

            //send time
            write(pfd[1], (char*)&t_end, sizeof(unsigned long));

            //close pipe and exit
            close(pfd[1]);
            exit(0);
        }
        // close read pipe
        close(pfd[0]);
        // if child ran first, t_end should be child start
    } while(ctime > t_end || t_end < t_start); 

    return t_end - t_start;

}
