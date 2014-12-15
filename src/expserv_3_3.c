/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/stat.h>
#include "cycles.h"

#define SOCK_PATH "/home/pi/exp_3_3_sock"
#define BYTES 14000

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, servlen, n;
     socklen_t clilen;
     struct sockaddr_un cli_addr, serv_addr;
     struct stat derp;
     char q;
     unsigned long t;

     while(1) {
     if((sockfd = socket(AF_UNIX, SOCK_STREAM,0)) < 0) {
       error("creating socket");
     }

     bzero((char*)&serv_addr,sizeof(serv_addr));
     serv_addr.sun_family = AF_UNIX;
     strcpy(serv_addr.sun_path, SOCK_PATH);
     servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

     printf("check1\n");

     stat(SOCK_PATH, &derp);
     while(errno != ENOENT) {
       stat(SOCK_PATH, &derp);
     }
     errno = 0;

     if(bind(sockfd, (struct sockaddr *)&serv_addr,servlen) < 0) {
       if(errno == EINVAL) {
         printf("%d\n", sockfd);
       }
       error("binding socket");
     }

     printf("check2\n");

     listen(sockfd, 5);
     printf("check3\n");
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,&clilen);
     if(newsockfd<0) {
       error("accepting");
     }
     printf("check4\n");
     //GET_HIGH(t);
     //write(sockfd, (char*)&t, sizeof(unsigned long));

     read(newsockfd, &q, 1);
     close(newsockfd);
     close(sockfd);
     if(q == '0') {
       return 0;
     }

     }
}
