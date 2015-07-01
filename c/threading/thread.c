/*************************************************************************
    > File Name: thread.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com 
    > Created Time: 2015年06月30日 星期二 09时34分11秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
char message[50] = "Hello world";
void * funcstart(void * arg){
	printf("thread starts running .... arg is %s\n",(char*)arg);
	sleep(2);
	strcpy(message,"I am the threading ..Bye!");
	pthread_exit("good bye threading ....\n");
}
int main(){
	int res;
	pthread_t pid;
	res = pthread_create(&pid,NULL,funcstart,(void*)message);
	if (res !=0 )
	{
		perror("error has happened....\n");
		printf("error occur...\n");
	}
	printf("waiting the thread ending...\n");
	void* th_res;
	res = pthread_join(pid,&th_res);
	if(res !=0)
	{
		printf("error return ..\n");

	}
	printf("return message is %s\n",(char*)th_res);
	printf("after thread ending .... message is %s\n",message);

	printf("thread....\n"); 
	return 0;
}

