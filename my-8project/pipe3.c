#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BUF_SIZE 100

int main(int argc,char *argv[])
{
    int fds1[2],fds2[2];//两个管道文件描述符
    char str1[]="这里是子进程。";
    char str2[]="这里是父进程。你是谁？";
    char buf[BUF_SIZE];
    pid_t pid;
    pipe(fds1);
    pipe(fds2);
    pid=fork();
    if(pid==0)
    {
        write(fds1[1],str2,sizeof(str2));
        read(fds2[0],buf,BUF_SIZE);
        printf("子进程输出:%s\n",buf);
    }
    else
    {
        read(fds1[0],buf,BUF_SIZE);
        printf("父进程输出:%s\n",buf);
        write(fds2[1],str1,sizeof(str1));
    }
    return 0;
}

// #include <stdio.h>
// #include <unistd.h>
// #define BUF_SIZE 30

// int main(int argc, char *argv[])
// {
//     int fds1[2], fds2[2];
//     char str1[] = "Who are you?";
//     char str2[] = "Thank you for your message";
//     char buf[BUF_SIZE];
//     pid_t pid;

//     pipe(fds1), pipe(fds2);
//     pid = fork();
//     if (pid == 0)
//     {
//         write(fds1[1], str1, sizeof(str1));
//         read(fds2[0], buf, BUF_SIZE);
//         printf("Child proc output: %s \n", buf);
//     }
//     else
//     {
//         read(fds1[0], buf, BUF_SIZE);
//         printf("Parent proc output: %s \n", buf);
//         write(fds2[1], str2, sizeof(str2));
//     }
//     return 0;
// }