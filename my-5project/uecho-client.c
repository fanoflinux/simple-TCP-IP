#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_MAXSIZE 100
void error_handling(char* message);

int main(int argc,char *argv[])
{
    /*定义相关参数*/
    int sockfd_clnt;
    char message[BUF_MAXSIZE];//区域
    int str_len;
    socklen_t cln_addr_len;//客户端长度
    struct sockaddr_in ser_addr,cln_addr;

    /*处理模块*/
    if(argc!=3)
    {
        printf("参数太少或这太多");
    } 
    sockfd_clnt=socket(AF_INET,SOCK_DGRAM,0);
    memset(&cln_addr,0,sizeof(cln_addr));
    cln_addr.sin_family=AF_INET;
    cln_addr.sin_addr.s_addr=inet_addr(argv[1]);
    cln_addr.sin_port=htons(atoi(argv[2]));

    while(1)
    {
        fputs("输入Q或者q则停止输入",stdout);
        fgets(message,sizeof(message),stdin);
        if(!strcmp(message,"q\n")||!(strcmp(message,"q\n")))
        break;
        sendto(sockfd_clnt,message,strlen(message),0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
        cln_addr_len=sizeof(cln_addr);
        str_len=recvfrom(sockfd_clnt,message,BUF_MAXSIZE,0,(struct sockaddr*)&cln_addr,&cln_addr_len);
        message[str_len]=0;\
        printf("从服务器来的消息是：%s",message);
    }
    close(sockfd_clnt);
    return 0;
}
void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}