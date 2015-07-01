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
int run_now = 1;
void * funcStart1(void * arg){
	int count=0;
	const int size = 20;
	while(count++ < size){
        if(run_now == 1 ){
            printf("1\n");
            run_now = 2;
        }else
        {
            sleep(1);
        }
	}
}
void * funcStart2(void * arg){
	int count=0;
	const int size = 20;
	while(count++ < size){
        if(run_now == 2 ){
            printf("2\n");
            run_now = 1;
        }else
        {
            sleep(1);
        }
	}
}
int main(){
	int res;
	pthread_t pid1,pid2;
	res = pthread_create(&pid1,NULL,funcStart1,(void*)message);

	if (res !=0 )
	{
		perror("error has happened....\n");
		printf("error occur...\n");
	}
	res = pthread_create(&pid2,NULL,funcStart2,(void*)message);
	if (res !=0 )
	{
		perror("error has happened....\n");
		printf("error occur...\n");
	}
	//printf("waiting the thread1 ending...\n");
	void* th_res;
	res = pthread_join(pid1,&th_res);
	if(res !=0)
	{
		printf("error return ..\n");

	}
	//printf("waiting the thread2 ending...\n");

	res = pthread_join(pid2,&th_res);
	if(res !=0)
	{
		printf("error return ..\n");
	}


	printf("thread ending ....\n");
	return 0;
}

