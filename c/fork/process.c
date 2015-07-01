/*************************************************************************
    > File Name: fork.c
    > Author:LIUHUAN
    > Mail: liu2012huan@126.com
    > Created Time: 2015年06月30日 星期二 10时56分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
	printf("exec running ...\n");
//	system("ps ax");
    char* file_path[] = {"PATH=/home/lainan/vlinux/c/threading/","path2=100",0};
    char* argvs[] = {"what's" ,"up","man",0};
    /**
    *execl(const char *path,argv0,argv1,...,0);
    *其中path表示要启动可执行文件的文件名，包括路径名
    *会默认的在系统环境变量PATH中搜寻，如果给定文件路径名，那么直接找这个文件
    *argv0,argv1....为可变参数列表，最后一个用(char*)0结束
	*/

	/**
    *execlp(const char *file,argv0,argv1,...,0);
    *其中file表示要启动可执行文件的文件名
    *文件名会默认的在系统环境变量PATH中搜寻，如果给定文件路径名，那么直接找这个文件
    *   argv0,argv1....为可变参数列表，最后一个用(char*)0结束
	*/

    /**
    *execle(const char *path,argv0,argv1,...,0,char* const envp[]);
    *其中path表示要启动可执行文件的文件名，可以不包括路径名，路径由envp给定
    *envp表示要搜索可执行文件的路径，文件目录
    *整个函数表示，在envp所指的文件路径下，搜索可执行文件path,并且给这个可执行文件的参数为
    *   argv0,argv1....0(结束)
	*/

    /**
        execv,execvp,execve
        与上面三个不同的就在于他们不是可变参数列表，而是把参数放在一个指针数组里面
    */

    /**
    *execv(const char *path,char*const argv[]);
    *其中path表示要启动可执行文件的文件名，可以不包括路径名，可以不包括路径名
    *文件名会默认的在系统环境变量PATH中搜寻
    *envp表示给可执行的文件设置环境变量
	*/

	/**
    *execvp(const char *file,char* const argv[]);
    *其中file表示要启动可执行文件的文件名，可以不包括路径名
    *文件名会默认的在系统环境变量PATH中搜寻
    *argv参数数组，最后一个参数用(char*)0结束
	*/


	/**
    *execve(const char *path,char* const argv[],char* const envp);
    *其中file表示要启动可执行文件的文件名，可以不包括路径名
    *文件名会默认的在系统环境变量PATH中搜寻
    *argv参数数组，最后一个参数用(char*)0结束
	*/

    /**规律
    *所有的函数调用都是通过系统调用函数execve实现的
    *int execve(const char *filename, char *const argv[],char *const envp[]);
    *所有带p结尾的函数会默认的在系统环境变量PATH中搜寻可执行文件，（在不指定可执行文件路径的情况下）
    *带l的函数都是可变参数的，不带l的是把可执行文件的参数放在一个指针数组里面
    *
    */



//	execl("/home/lainan/vlinux/c/threading/thread3","thread2","what's up man ",0);
//    execle("/home/lainan/vlinux/c/threading/thread3","what's ","up" ,"man",0,file_path);
    char * exefile = "/home/lainan/vlinux/c/threading/thread4";
    execve("./../threading/thread4",argvs,file_path);
	printf("done...\n");
	return 0;
}

