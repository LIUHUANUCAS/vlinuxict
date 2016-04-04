/*************************************************************************
    > File Name: server.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com
    > Created Time: 2015年06月30日 星期二 10时56分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<pthread.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
int main(){

  int sockfd, n;
  struct sockaddr_in clientAddr;
  char line[300];
  bzero(&clientAddr, sizeof(clientAddr));

  //Init Socket params.
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  clientAddr.sin_port = htons(8080);
  //IPV4  SOCK_DGRAM socket UDP protocol
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd <= 0)
      return 0;

  //Set recv buffer size.
  int RecBufLen = 128 * 1024 * 1024;
  if(setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (char *)&RecBufLen, sizeof(int)) < 0)
      printf("Socket setopt recv buffer error..\n");
  //Set recv timeout.
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 100; //100us
  if(  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval)) < 0 )
      printf("Socket setopt timeout error..\n");

  bind(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  socklen_t len;
  len= sizeof(struct sockaddr);
  //server start
  for ( ; ; ){
    printf("recv one \n");
      // n = recvfrom(sockfd,line,sizoef(line),0,(struct sockaddr *)clientAddr,0);
      n = recvfrom(sockfd, line, sizeof(line), 0, (struct sockaddr *)&clientAddr, &len);
      // n = recv(sockfd, line, sizeof(line), 0);
      printf("ip=%s\n",inet_ntoa(clientAddr.sin_addr));

  }
	printf("done...\n");
	return 0;
}
