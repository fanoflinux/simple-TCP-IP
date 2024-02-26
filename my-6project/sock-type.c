#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void error_handling(char *message);

int main(int argc,char *argv[])
{
    int tcp_sock,udp_sock;
    int sock_type;
    socklen_t optlen;
    int state;

    optlen=sizeof(sock_type);
    tcp_sock=socket(AF_INET,SOCK_STREAM,0);
    udp_sock=socket(AF_INET,SOCK_DGRAM,0);
    printf("SOCK_STREAM:%d\n",SOCK_STREAM);
    printf("SOCK_DGRAM:%d\n",SOCK_DGRAM);

    state=getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
    if(state)
        error_handling("getsockopt()error!\n");
    printf("socket type 1:%d\n",state);
    state=getsockopt(udp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
    if(state)
        error_handling("getsockopt()error!\n");
    printf("socket type 2:%d\n",state);

    return 0;
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}