#include<stdio.h>
#include<stdlib.h>
#include<sys/signal.h>
#include<unistd.h>

void print_message(int sig)
{
    if(sig==SIGALRM)
    {
        puts("程序超时");
    }
    alarm(2);
}
int main(int argc,char *argv[])
{
    signal(SIGALRM,print_message);
    alarm(2);
    for(int i=0;i<5;i++)
    {
        puts("等待…………");
        sleep(1);
    }
    return 0;
}