/* Network experiment 3 2: output bandwidth, remote
 * This experiment measures the peak output bandwidth.
 * It does this by establishing a connection with a 
 * remote server, and measuring the time for a write
 * to complete on a large message. 
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
#define PORT 1337
#define BYTES 14000

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;
//char buffer[256];
unsigned long t;
char bigpacket[BYTES];

void setup()
{
    //portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    server = gethostbyname(HOST);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(1);
    }

    portno = PORT;

    //fill with zeroes?
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    int i;
    for(i = 0; i < BYTES; ++i) {
      bigpacket[i] = '1';
    }
}

unsigned long measure() {

    char q;
    RESET;
    write(sockfd,bigpacket,BYTES);
    read(sockfd,&q,1);
    GET_HIGH(t);
    return t;
}

void teardown() {
    // send shutdown message
    write(sockfd, "0", 1);
    close(sockfd);
}
