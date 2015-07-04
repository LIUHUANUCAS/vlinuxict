/*************************************************************************
    > File Name: semaphore.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com
    > Created Time: 2015年07月03日 星期五 15时23分09秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/sem.h>
#include<time.h>
#include <semaphore.h>
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
void delete_semvalue();
int set_semvalue();
int semaphore_p();
int semaphore_v();
int sem_id;
int main(int argc,char* argv[]){
	/**1.获取信号，初始化*/
    char ch = 'O';
	key_t key = (key_t)1234;
	sem_id = semget(key,1,0666| IPC_CREAT);
	if(argc > 1 ){
        if(!set_semvalue()){
                printf("set value error\n");
                exit(1);
        }
        ch = 'X';
        sleep(2);
	}
	int i;
	for(i=0;i<10;++i){
        if(!semaphore_p())
            exit(-1);
        printf("%c",ch);
        fflush(stdout);
        sleep(2);
        printf("%c",ch);
        fflush(stdout);
        if(!semaphore_v())
            exit(-1);
        sleep(3);
	}
	printf("finished .....\n");
	if(argc > 1){
        sleep(10);
        delete_semvalue();
	}
	exit(0);

}
int set_semvalue(){
    union semun sem_union;
    sem_union.val = 1;

    /**初始化信号量,0表示这个进程第一个也是唯一一个信号量*/
    int flag = semctl(sem_id,0,SETVAL,sem_union) ;
    if(flag == -1)
        return 0;
    return 1;

}

void delete_semvalue(){
    union semun sem_union;
    /**删除信号量*/
    int flag = semctl(sem_id,0,IPC_RMID,sem_union) ;
    if(flag == -1)
        printf("delete semaphore error....\n");

}

int semaphore_v(){
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    /**设置为V操作的标志位,对信号量进行+1操作*/
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    /**对信号量进行V 操作*/
    int flag = semop(sem_id,&sem_b,1);
    if(flag == -1){
        printf("v operator error...\n");
        return 0;
    }
    return 1;
}

int semaphore_p(){
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    /**设置为P操作的标志位,对信号量进行-1操作*/
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    /**对信号量进行P 操作*/
    int flag = semop(sem_id,&sem_b,1);
    if(flag == -1){
        printf("p operator error...\n");
        return 0;
    }
    return 1;
}
