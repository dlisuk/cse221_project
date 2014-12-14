#include "basic_experiment.c"

#include <stdio.h>
 #include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//David: update this when you get home
#define HOST "111.222.121.212"
#define PORT 1337

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void setup(){}
void teardown(){}

int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;

unsigned long t;
char q;

unsigned long measure() {

    portno = PORT;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    server = gethostbyname(HOST);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    //fill with zeroes?
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    int l;
    reset();
    l = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
    GET_HIGH(t);
    if(l < 0) {
        error("ERROR connecting");
    }

    write(sockfd,"1",1);
    if (n < 0) {
         error("ERROR writing to socket");
    }
    n = read(sockfd,&q,1);
    if (n < 0) {
         error("ERROR reading from socket");
    }
    close(sockfd);
    return t;
}
