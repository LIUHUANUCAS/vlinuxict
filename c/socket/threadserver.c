/*************************************************************************
    > File Name: threadserver.c
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
#include<pthread.h>
void * dealClient(void * arg){
    int clientid = (int)arg;
    printf("client id:%d\n",clientid);
    char ch = 'b';
    while(ch <= 'z' ){
        write(clientid,&ch,1);
        printf("char : %c\n",ch);
        ch++;
    }
    close(clientid);
    pthread_exit("thread exit ..\n");
}

int main(){

    int serverid,client_id;
    int server_len,client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    int result;



    /**1.创建套接字*/
    char* server_socket_name = "server_socket";
    /**取消原来的套接字连接，如果存在的话*/
    unlink(server_socket_name);
    serverid = socket(AF_UNIX,SOCK_STREAM,0);
    /**2命名套接字*/
    server_address.sun_family = AF_UNIX;
    /**设置套接字的名字*/
    strcpy(server_address.sun_path,server_socket_name);
    server_len = sizeof(server_address);
    /**3.绑定端口和地址*/
    bind(serverid,(struct sockaddr *)&server_address,server_len);
    /**4.监听端口*/
    /**这个socket上可以连接客户端的数目*/
    int queuelen = 5;
    listen(serverid,queuelen);

    while(1) {
        const int size = 3;
        char ch;
        char buf[size];
        printf("server is listening...\n");
        client_len = sizeof(client_address);
        /**接受一个客户端连接*/
        client_id = accept(serverid,(struct sockaddr *)&client_address,&client_len);
        printf("connecting a client ...\n");
        /**从客户端读取数据*/
        pthread_t pid;

        pthread_create(&pid,NULL,dealClient,(void*) client_id);

        printf("end for service a client \n");
    }
    close(serverid);


//	printf("exec running ...\n");
//    char* file_path[] = {"PATH=/home/lainan/vlinux/c/threading/","path2=100",0};
//    char* argvs[] = {"what's" ,"up","man",0};
//    pid_t pid;
//    pid = fork();
//    if(pid == 0){
//        printf("in child...\n");
//        execve("/home/lainan/vlinux/c/threading/thread4",argvs,file_path);
//    }
//    else if(pid > 0 ){
//
//    }
//    execle("/home/lainan/vlinux/c/threading/thread3","what's ","up" ,"man",0,file_path);
//    char * exefile = "/home/lainan/vlinux/c/threading/thread4";
//    execve("./../threading/thread4",argvs,file_path);
	printf("done...\n");
	return 0;
}

