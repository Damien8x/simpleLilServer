#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
 
int sockfd, newsockfd, portno, n, k;
unsigned int clien;
k=0;
char buffer[256];
char bufferReverse[256];
/*
defined in <netinet/in.h>
struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};
*/
struct sockaddr_in serv_addr, cli_addr;

sockfd = socket(AF_INET, SOCK_STREAM, 0);

bzero((char *) &serv_addr, sizeof(serv_addr));

portno = atoi(argv[1]);

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(portno);
serv_addr.sin_addr.s_addr = INADDR_ANY;

bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

listen(sockfd, 1);

while(true){

clien = sizeof(cli_addr);
newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clien);

bzero(buffer,256);
n = read(newsockfd,buffer,255);
printf("Here is the message: %s\n",buffer);

for(int i = (n-1); i >= 0; i--)
{
	bufferReverse[k] = buffer[i];
	k++; 
}

n = write(newsockfd, bufferReverse, strlen(buffer));

bzero(bufferReverse,256);

close(newsockfd);
}

close(sockfd);

}

