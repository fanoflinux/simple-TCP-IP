#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void ctrl_hanlding(int sig);

int main(int argc,char *argv[])
{
    struct sigaction act;
    act.sa_handler=ctrl_hanlding;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGINT,&act,0);

    while(1)
    {
        sleep(3);
        printf("你好！\n");
    }
    return 0;
}
void ctrl_hanlding(int sig)
{
    char c;
    if(sig==SIGINT)
    {
        fputs("请确认是否结束程序(输入'Y'表示结束)",stdout);
        scanf("%c",&c);
        if(c=='Y'||c=='y')
        {exit(1);}
    }
}