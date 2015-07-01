/*************************************************************************
    > File Name: forkclient.c
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
int main(int argc,char* argv[]){

    int client_id;
    int client_len;
//    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    int result;



    /**1.创建套接字*/
    char* server_socket_name = "server_socket";
    /**取消原来的套接字连接，如果存在的话*/
//    unlink(server_socket_name);
    client_id = socket(AF_UNIX,SOCK_STREAM,0);
    /**2命名套接字*/
    client_address.sun_family = AF_UNIX;
    /**设置套接字的名字，这里根据服务器的套接字信息命名*/
    strcpy(client_address.sun_path,server_socket_name);
    client_len = sizeof(client_address);
    /**3.连接服务器的端口*/
    result = connect(client_id,(struct sockaddr * )&client_address,client_len);
    if(result == -1 ){
        printf("error connect to server ....\n");
        exit(1);
    }
    char ch = 'A';
    const int size =3;
    char buf[size];
    strcpy(buf,"Aa");
    /**4.和服务器通信*/
    result = read(client_id,&ch,1);
    while(result > 0){
        printf("reslut->%d\n",result);
         /**从服务器读取数据*/
        printf("char from server is :%c\n",ch);
        result = read(client_id,&ch,1);
    }
    close(client_id);
    printf("client end connection to server ...\n");


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

