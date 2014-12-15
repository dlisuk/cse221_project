/* A simple server in the internet domain using TCP
   The port number is passed as an argument
   see client_3_2_in.c for more details 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

//David: change this host to your laptop's ip
#define PORT 1337
#define BYTES 14000

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[BYTES];
     char q;
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     for(n = 0; n < BYTES; ++n) {
       buffer[n] = '1';
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = PORT;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

     while(1) {
     read(newsockfd, &q, 1);
     if(q == '0') {
       close(newsockfd);
       close(sockfd);
       return 0;
     }
     n = write(newsockfd,buffer,BYTES);
     if (n < 0) error("ERROR writing to socket");
     };
}
