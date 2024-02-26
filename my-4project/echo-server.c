#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc,char *argv[])
{
    //创建通信与连接套接字
    int sockfd_listen;
    int sockfd_connect;
    //消息数组
    char message[BUF_SIZE];
    int str_len;
    //端口+IP地址
    struct sockaddr_in serv_adr;//服务器IP+端口
    struct sockaddr_in clnt_adr;//客户端IP+端口
    socklen_t clnt_adr_sz;

    if(argc !=2)
    {
        printf("Usage : %s<port> \n",argv[0]);
    }
    //创建通信套接字
    sockfd_listen = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd_listen == -1)
    {
        error_handling("创建连接套接字错误 \n");
    }

    //将相关信息置为初值
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;//设置协议族
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);//设置为回送地址。注意将主机字节序转换为网络字节序
    serv_adr.sin_port = htons(atoi(argv[1]));//设置端口号，注意将主机字节序转换为网络字节序

    //绑定套接字与端口+IP地址，用来接听客户端传来的信号
    if(bind(sockfd_listen,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
    {
        error_handling("绑定失败\n");
    }
    if(listen(sockfd_listen,5)==-1)//监听5个目标
    {
        error_handling("失去监听目标");
    }
    clnt_adr_sz = sizeof(clnt_adr);
    for(int i =0;i<5;i++)//回传五次信息
    {
        sockfd_connect=accept(sockfd_listen,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
        if(sockfd_connect==-1)
        {
            error_handling("未被成功接收或客户端停止服务器访问");
        }
        else
        {
            printf("连接的客户端为 %d \n",i+1);
        }
        while((str_len=read(sockfd_connect,message,BUF_SIZE))!=0)
        {
            write(sockfd_connect,message,str_len);
        }
        close(sockfd_listen);
    }
    close(sockfd_listen);

    return 0;
}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}