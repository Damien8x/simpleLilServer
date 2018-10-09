//http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
using namespace std;

int main(int argc, char *argv[])
{

int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;

char buffer[256];
string input(argv[3]);
strcpy(buffer, input.c_str());
portno = atoi(argv[2]);
sockfd = socket(AF_INET, SOCK_STREAM, 0);

server = gethostbyname(argv[1]);

bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
bcopy((char *)server->h_addr, 
(char *)&serv_addr.sin_addr.s_addr,
server->h_length);
serv_addr.sin_port = htons(portno);

connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

n=write(sockfd,buffer,strlen(buffer));

bzero(buffer, 256);
n=read(sockfd,buffer,255);

printf("%s", buffer);

close(sockfd);
return 0;


}
