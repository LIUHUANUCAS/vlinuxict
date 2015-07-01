/*************************************************************************
    > File Name: dealclient.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com
    > Created Time: 2015年06月30日 星期二 10时56分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>

//liu
int main(int argc,char* argv[]){
    if(argc != 2){
        printf("paramater error...\n");
        exit(1);
    }
    printf("in a new process...\n");

    int clientid =  atoi( argv[1]);
    int id=10;
    sprintf(argv[1],"%d",id);
    char ch = clientid%6 + 'a';
    printf("clientid :%d\n",clientid);
    printf("ar1 %s\n",argv[1]);
    printf("ar0 %s\n",argv[0]);
//    return 0;
    while(ch <= 'z' ){
        write(clientid,&ch,1);
        printf("char : %c\n",ch);
        ch++;
    }
//    write()
//    sleep(3);
    close(clientid);

	printf("done...\n");
	printf("end for service a client \n");
//	exit(0);
	return 0;
}

