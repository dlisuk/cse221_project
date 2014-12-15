#include "basic_experiment.c"

//#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
//#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>


//David: update the host to your IP when you run these tests
#define SOCK_ADDR "/home/pi/exp_3_2_in_sock"
#define BYTES 14000

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int sockfd, servlen, n;
struct sockaddr_un serv_addr;
unsigned long t;
char bigpacket[BYTES];

void setup()
{


    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCK_ADDR);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
      error("Creating socket");
    }
    if(connect(sockfd, (struct sockaddr *)&serv_addr, servlen) < 0) {
      error("Connecting");
    }

}

unsigned long measure() {

    write(sockfd,"1",1);
    RESET;
    read(sockfd,bigpacket,BYTES);
    GET_HIGH(t);
    return t;
}

void teardown() {
    // send shutdown message
    write(sockfd, "0", 1);
    close(sockfd);

    int x = 3+strlen(SOCK_ADDR)+1;
    char * rmcmd=(char*)malloc(x);
    strcpy(rmcmd, "rm ");
    strcat(rmcmd, SOCK_ADDR);
    rmcmd[x-1]=0;
    //printf("remove command:\n%s\n", rmcmd);
    system(rmcmd);
    free(rmcmd);
}
