/*************************************************************************
    > File Name: sharemem1.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com
    > Created Time: 2015年07月01日 星期三 16时08分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/shm.h>
#include<string.h>
#include "share.h"

int main(){
    int running = 1;
    void * shared_memory = 0;
    struct shared_use_st * shared_stuff= 0;
    int shmid;
    srand(getpid());
    char buffer[BUFSIZ];
    /**1.创建共享内存段*/
    //内存段名字
    key_t key = (key_t)1234;
    shmid = shmget(key,sizeof(struct shared_use_st),0666|IPC_CREAT);

    if(shmid == -1){
        printf("shmget error..\n");
        exit(-1);
    }
    /**2.将共享内存段共享到一个进程的地址空间里面*/
    //share_memory 指向共享内存段的起始地址
    shared_memory = shmat(shmid,0,0);
    if(shared_memory == (void*)-1){
        printf("error shmat ...\n");
        exit(-1);
    }

    printf("shared memory  attache at %X\n",(int)shared_memory);


    /**3.开始对共享内存段进行写操作*/

    shared_stuff = (struct shared_use_st * )shared_memory;
    shared_stuff->written_by_you = 0;

    while(running){

        while(shared_stuff->written_by_you == 1){
            sleep(1);
            printf("wait for client..\n");

        }
        printf("enter some text ..\n");
        fgets(buffer,BUFSIZ,stdin);
        printf("buffer is -> %s\n",buffer);

        strncpy(shared_stuff->some_text,buffer,TEXT_SIZE);
        shared_stuff->written_by_you = 1;
        if(strncmp(shared_stuff->some_text,"end",3) == 0){
            running = 0;
        }
    }//end while



    /**4.分离共享内存段*/

    //分离共享内存段
    if(shmdt(shared_memory) == -1){
        printf("detach share memory error...\n");
        exit(-1);
    }



    exit(0);




}


