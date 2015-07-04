/*************************************************************************
    > File Name: msgqueue2.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com
    > Created Time: 2015年07月03日 星期五 16时28分18秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<sys/msg.h>
#include<string.h>
struct my_msg_st{
    long int my_msg_type;
    char some_text[BUFSIZ];
};
int main(int argc,char* argv[]){
    /**1.建立消息队列*/
    int msgid;
    msgid = msgget((key_t)1234,0666|IPC_CREAT);
    if(msgid == -1){
        printf("error get queue...\n");
        exit(-1);
    }
    char buff[BUFSIZ];
    int running = 1;
    struct my_msg_st some_data;
    long int msg_to_receive = 0;
    while(running){


            /**2.访问消息队列，从消息队列中读取信息*/

            if(msgrcv(msgid,(void*)&some_data,BUFSIZ,msg_to_receive,0) == -1){
                printf("receive message error...\n");
                exit(-1);
            }

            printf("you write :%s",some_data.some_text);
            if(strncmp(some_data.some_text,"end",3) == 0)
                running = 0;

    }

    /**3.移除系统中的消息队列*/
    if(msgctl(msgid,IPC_RMID,0) == -1)
        exit(-1);
    exit(0);
}




