/*********************************************************
* File Name: select.c
* Author: LIUHUAN
* Email: liu2012huan@126.com | liuhuan@ict.ac.cn
* Created Time: 2016年04月04日 星期一 10时14分06秒
*********************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
	char buffer[128];
	int result,nread;
	fd_set inputs,testfds;
	struct timeval timeout;
	FD_ZERO(&inputs);
	FD_SET(0,&inputs);
	while(1){
		testfds = inputs;
		timeout.tv_sec=2;
		timeout.tv_usec=5000;
		result = select(FD_SETSIZE,&testfds,NULL,NULL,&timeout);
		switch(result){
			case 0:
				printf("timeot\n");
				break;
			case -1:
				perror("select");
				exit(1);
			default:
				if(FD_ISSET(0,&testfds)){
					ioctl(0,FIONREAD,&nread);
					if(nread == 0){
						printf("keyboard done\n");
						exit(0);
					}
					nread = read(0,buffer,nread);
					buffer[nread]= 0;
					printf("read %d from keyboard %s\n",nread,buffer);
				}
				break;

		}
	}
}

