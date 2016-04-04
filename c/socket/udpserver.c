#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#define	UDP_TEST_PORT		50001

ssize_t						/* Read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = (char*)vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return(-1);
		} else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);		/* return >= 0 */
}
/* end readn */


int main(int argC, char* arg[])
{
	struct sockaddr_in addr;
	int sockfd, len = 0;
	int addr_len = sizeof(struct sockaddr_in);
	const int bsize = sizeof(struct timeval) + 2*sizeof(int);
	char buffer[bsize];

	/* 建立socket，注意必须是SOCK_DGRAM */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror ("socket");
		exit(1);
	}

	/* 填写sockaddr_in 结构 */
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(UDP_TEST_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY) ;// 接收任意IP发来的数据

	/* 绑定socket */
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))<0) {
		perror("connect");
		exit(1);
	}

	while(1) {
		bzero(buffer, sizeof(buffer));
		len = readn(sockfd,buffer,sizeof(struct timeval));
		// len = recvfrom(sockfd, buffer, sizeof(struct timeval), 0,
					  //  (struct sockaddr *)&addr ,&addr_len);
		/* 显示client端的网络地址和收到的字符串消息 */
		printf("Received a string from client %s,\n",
				inet_ntoa(addr.sin_addr));
		struct timeval end;
		memcpy(&end,buffer,sizeof(struct timeval));
		printf("%ld,%ld\n",end.tv_sec,end.tv_usec);
		// len = recvfrom(sockfd,buffer,2*sizeof(int),0,(struct sockaddr *)&addr ,&addr_len);
		len  = readn(sockfd,buffer,sizeof(int)*2);
		int a;
		memcpy(&a,buffer,sizeof(int));
		printf("a = %d\n",a);
		memcpy(&a,buffer+sizeof(int),sizeof(int));
		printf("a2= %d\n",a);
		/* 将收到的字符串消息返回给client端 */
		sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
	}

	return 0;
}

// ----------------------------------------------------------------------------
// End of udp_server.c
