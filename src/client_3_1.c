/* Network experiment 1: RTT, remote
 * tests RTT by setting up connection
 * with remote server, sends a single
 * packet, records time between 
 * completion of socket write and 
 * reception of response from server
 */

#include "basic_experiment.c"

//#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
//#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


//David: update the host to your IP when you run these tests
#define HOST "192.168.1.166"
#define PORT 2000

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;
//char buffer[256];
char * msgstring = "1";
unsigned long t;

void setup()
{
    //portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    printf("socket established\n");

    server = gethostbyname(HOST);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(1);
    }

    printf("host naem get\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(PORT);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    printf("connect get!\n");

}

unsigned long measure() {

    char q;
    write(sockfd,"1",1);
    RESET;
    read(sockfd,&q,1);
    GET_HIGH(t);
    return t;
}

void teardown() {
    // send shutdown message
    write(sockfd, "0", 1);
    close(sockfd);
}
