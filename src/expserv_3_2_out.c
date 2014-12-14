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

#define SOCK_PATH "/home/pi/exp_3_2_out_sock"
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
     char bigpacket[BYTES];
     char q;

     if((sockfd = socket(AF_UNIX, SOCK_STREAM,0)) < 0) {
       error("creating socket");
     }

     bzero((char*)&serv_addr,sizeof(serv_addr));
     serv_addr.sun_family = AF_UNIX;
     strcpy(serv_addr.sun_path, SOCK_PATH);
     servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

     if(bind(sockfd, (struct sockaddr *)&serv_addr,servlen) < 0) {
       if(errno == EINVAL) {
         printf("%d\n", sockfd);
       }
       error("binding socket");
     }

     listen(sockfd, 5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,&clilen);
     if(newsockfd<0) {
       error("accepting");
     }

     while(1) {
       read(newsockfd,&q,1);
       if(q != '1') {
         close(newsockfd);
         close(sockfd);
         return 0;
       }
       read(newsockfd,bigpacket,BYTES-1);
       write(newsockfd,"k",1);
     }
}
