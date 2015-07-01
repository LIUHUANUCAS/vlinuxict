/*************************************************************************
    > File Name: clockalarm.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com
    > Created Time: 2015年07月01日 星期三 17时07分59秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void clockalarm(int sig){
    printf("It's time ...ding...ding...\n");

}
int main(){
    struct sigaction act;
    act.sa_handler = clockalarm;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT,&act,0);
    while(1){
        printf("sleep time ....\n");
        sleep(1);
    }

}


