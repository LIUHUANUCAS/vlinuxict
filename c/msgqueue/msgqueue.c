/*************************************************************************
    > File Name: msgqueue.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com
    > Created Time: 2015年07月03日 星期五 16时28分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<string.h>
struct my_msg_st{
    long int my_msg_type;
    char some_text[BUFSIZ];
};
int main(int argc,char* argv[]){
    /**1.连接消息队列*/
    int msgid;
    msgid = msgget((key_t)1234,0666|IPC_CREAT);
    if(msgid == -1){
        printf("error get queue...\n");
        exit(-1);
    }
    char buff[BUFSIZ];
    int running = 1;
    struct my_msg_st some_data;

    while(running){
            printf("enter some text..\n");
            fgets(buff,BUFSIZ,stdin);
            some_data.my_msg_type = 1;
            strcpy(some_data.some_text,buff);

            /**2.访问消息队列，向消息队列中写信息*/
            if(msgsnd(msgid,(void*)&some_data,BUFSIZ,0 ) == -1)
                exit(-1);


            printf("somedata:%s",some_data.some_text);
            if(strncmp(some_data.some_text,"end",3) == 0)
                running = 0;

    }


    exit(0);
}


