#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_MAXSIZE 100
void error_handling(char *message);

int main(int argc,char *argv[])
{
    /*定义相关变量*/
    int sockfd_serv;//只用定义
    char message[BUF_MAXSIZE];//定义数组长度
    int str_len;//字符串长度
    socklen_t clnt_addr_len;//客户端长度
    struct sockaddr_in serv_addr,clnt_addr;//定义客户端服务器地址

    /*处理模块*/
    if(argc!=2)
    {
        printf("参数过多或者过少引起异常");
    }
    sockfd_serv=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd_serv==-1)
    {
        error_handling("生成套接字失败");
    }
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(sockfd_serv,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
    {
        error_handling("绑定失败");
    }
    /*消息处理*/
    while(1)
    {
        clnt_addr_len=sizeof(clnt_addr);
        str_len=recvfrom(sockfd_serv,message,BUF_MAXSIZE,0,(struct sockaddr*)&clnt_addr,&clnt_addr_len);
        sendto(sockfd_serv,message,str_len,0,(struct sockaddr*)&clnt_addr,clnt_addr_len);
    }
    close(sockfd_serv);
    return 0;
}
void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}