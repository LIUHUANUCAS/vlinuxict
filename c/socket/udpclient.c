#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#define	UDP_TEST_PORT		50001
#define UDP_SERVER_IP 		"127.0.0.1"

int main(int argC, char* arg[])
{
	struct sockaddr_in addr;
	int sockfd, len = 0;
	int addr_len = sizeof(struct sockaddr_in);
	char buffer[256];

	/* 建立socket，注意必须是SOCK_DGRAM */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	/* 填写sockaddr_in*/
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(UDP_TEST_PORT);
	addr.sin_addr.s_addr = inet_addr(UDP_SERVER_IP);

	while(1) {
		bzero(buffer, sizeof(buffer));

		printf("Please enter a string to send to server: \n");

		/* 从标准输入设备取得字符串*/
		len = read(STDIN_FILENO, buffer, sizeof(buffer));
		struct timeval time ;
		gettimeofday(&time,0);
		printf("%ld,%ld\n",time.tv_sec,time.tv_usec);
		memcpy(buffer,&time,sizeof(struct timeval));
		sendto(sockfd, buffer, sizeof(struct timeval), 0, (struct sockaddr *)&addr, addr_len);
		int c = 100;
		memcpy(buffer,&c,sizeof(int));
		c=200;
		memcpy(buffer+sizeof(int),&c,sizeof(int));

		/* 将字符串传送给server端*/
		sendto(sockfd, buffer, 2*sizeof(int), 0, (struct sockaddr *)&addr, addr_len);

		/* 接收server端返回的字符串*/
		len = recvfrom(sockfd, buffer, sizeof(buffer), 0,
				       (struct sockaddr *)&addr, &addr_len);
		printf("Receive from server: %s\n", buffer);
	}

	return 0;
}

// ----------------------------------------------------------------------------
// End of udp_client.c
