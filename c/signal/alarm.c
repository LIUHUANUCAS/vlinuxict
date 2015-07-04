/*************************************************************************
    > File Name: alarm.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com 
    > Created Time: 2015年07月03日 星期五 09时35分34秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void ding(){
	printf("ding...ding...ding...\n");
}
int main(){
	signal(SIGALRM,ding);
	printf("beign sleep....\n");
	alarm(2);
	int i;
//	for(i=0;i<20;++i){
//		printf("sleep ...\n");
		sleep(2);

//	}
	printf("I sleep 2s..\n");

	printf("I am wake ...\n");
	return 0;
}

 
