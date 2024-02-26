#include<stdio.h>
#include<unistd.h>

int main()
{
    __pid_t pid=fork();
    if(pid==0)
    {
        puts("hi,i am a child process");
    }
    else
    {
        printf("child process ID:%d\n",pid);
        sleep(60);
    }

    if(pid==0)
    {
        puts("End child process");
    }
    else
    {
        puts("End parent process");
    }
    return 0;
}