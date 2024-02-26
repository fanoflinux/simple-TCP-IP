#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 30

int main(int argc,char *argv[])
{
    fd_set reads,temps;
    int result,str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;

    FD_ZERO(&reads);
    FD_SET(0,&reads);
    printf("请输入要键入的内容:");
    while(1)
    {
        temps=reads;
        timeout.tv_sec=2;
        timeout.tv_usec=0;
        result=select(2,&temps,0,0,&timeout);
        if(result==-1)
        {
            puts("复用错误");
            break;
        }
        else if(result==0)
        {
            puts("超时了,请输入");
        }
        else
        {
            if(FD_ISSET(0,&temps))
            {
                str_len=read(0,buf,BUF_SIZE);
                buf[str_len]=0;
                printf("键入的消息为:%s\n",buf);
            }
        }
    }
    return 0;
}