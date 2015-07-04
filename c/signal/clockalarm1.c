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
void clockalarm(int a){
    printf("ding...ding...ding...\n");
	alarm(3);
}
int main(){
    struct sigaction act;
    act.sa_handler = clockalarm;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM,&act,0);
	alarm(2);
    while(1){
        printf("sleep time ....\n");
        sleep(1);
    }

}


