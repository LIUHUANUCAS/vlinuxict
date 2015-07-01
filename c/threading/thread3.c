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
    printf("thread beging...\n");
//    int number = *(int *)arg;
    int number = (int)arg;
    int n=10;
    printf("threading %d\n",number);
//    n = (int)(rand()%3);
    n = 1 + (int)(0.9*rand()/ (RAND_MAX+1.0));
    sleep(n);
    printf("bye from %d\n",number);
}
int main(int args,char* argv[]){
    int i;
    for (i=0; environ[i]!=NULL; ++i)
    {
        printf("%s\n", environ[i]);
    }
    //for()
	int res;
//	char* env = getenv(argv[0]);
//	printf("%s",env);
//	return 0;
	const int NUM_THREAD = 10;
	pthread_t pid[NUM_THREAD];
	int i;
	for(i=0;i<args;++i)
        printf("args[%d]=%s\n",i,argv[i]);

	for(i=0;i<NUM_THREAD;++i){
	    res = pthread_create(pid+i,NULL,funcstart,(void*)i);
	    if (res !=0 )
        {
            perror("error has happened....\n");
            printf("error occur...\n");
        }
//        sleep(1);
	}


	printf("waiting the thread ending...\n");
	void* th_res;
	for(i=NUM_THREAD-1;i>=0;--i){
        res = pthread_join(pid[i],NULL);
        if(res !=0)
        {
            printf("error return ..\n");

        }
	}


	printf("thread....\n");
	return 0;
}

