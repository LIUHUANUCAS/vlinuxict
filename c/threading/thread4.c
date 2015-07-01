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
extern char** environ;

int main(int args,char* argv[]){
    int i;
    printf("environment variable\n");
    printf("==============begin======\n");
    i=0;
    char** p = environ;
    while(*p){
        printf("%s\n",*p);
        p++;
    }
    printf("==============end=========\n");
    printf("============argvs=========\n");
    for(i=0;i<args;++i)
        printf("%s\n",argv[i]);
    printf("============end===========\n");
	return 0;
}

