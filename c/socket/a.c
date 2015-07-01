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
int main(){

    int server;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';



	printf("exec running ...\n");
    char* file_path[] = {"PATH=/home/lainan/vlinux/c/threading/","path2=100",0};
    char* argvs[] = {"what's" ,"up","man",0};
    pid_t pid;
    pid = fork();
    if(pid == 0){
        printf("in child...\n");
        execve("/home/lainan/vlinux/c/threading/thread4",argvs,file_path);
    }
    else if(pid > 0 ){

    }
//    execle("/home/lainan/vlinux/c/threading/thread3","what's ","up" ,"man",0,file_path);
//    char * exefile = "/home/lainan/vlinux/c/threading/thread4";
//    execve("./../threading/thread4",argvs,file_path);
	printf("done...\n");
	return 0;
}

