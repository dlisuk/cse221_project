#include "basic_experiment.c"

//#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
//#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>


//David: update the host to your IP when you run these tests
#define SOCK_ADDR "/home/pi/exp_3_3_sock"
#define BYTES 14000

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int sockfd, servlen, n;
struct sockaddr_un serv_addr;
unsigned long t, t2;
char q;
char * curmsg = "1";
struct stat derp;

void setup()
{
numTrials = 800;
}

unsigned long measure() {
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCK_ADDR);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
      error("Creating socket");
    }

    stat(SOCK_ADDR, &derp);
    while(errno == ENOENT) {
      errno = 0;
      stat(SOCK_ADDR, &derp);
    }
    printf("%d\n", errno);

    RESET;
    connect(sockfd, (struct sockaddr *)&serv_addr, servlen);
    GET_HIGH(t);
    while(errno) {
      if(errno == ECONNREFUSED) {
        errno = 0;
        RESET;
        connect(sockfd, (struct sockaddr *)&serv_addr, servlen);
        GET_HIGH(t);
      }
      printf("errno %d\n", errno);
    }

    //read(sockfd,(char*)&t2, sizeof(unsigned long));
    write(sockfd, curmsg, 1);
    close(sockfd);

    int x = 3+strlen(SOCK_ADDR)+1;
    char * rmcmd=(char*)malloc(x);
    strcpy(rmcmd, "rm ");
    strcat(rmcmd, SOCK_ADDR);
    rmcmd[x-1]=0;
    system(rmcmd);
    free(rmcmd);

    //return (t<t2)?t:t2;
    return t;

}

void teardown() {
   curmsg = "0";
   measure();
}
