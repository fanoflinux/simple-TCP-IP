#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void print(int sig)
{
   if(sig==SIGUSR1)
   {
     puts("这是一个偶数");
   }
}
int main(int argc,char *argv[])
{
    struct sigaction sa;
    // 设置 SIGUSR1 信号处理函数
    sa.sa_handler = print;
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    sleep(1);

    for(int i=0;i<4;i++)
    {
        printf("打印的数字为%d\n",i);
        if(i%2==0)
        {
            kill(getpid(),SIGUSR1);
        }
        sleep(1);
    }
    return 0;
}