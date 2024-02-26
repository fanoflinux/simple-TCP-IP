#include<stdio.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
    unsigned short host_port = 0X1234;
    unsigned short net_port;

    unsigned long host_addr = 0X12345678;
    unsigned long net_addr;

    net_port = htons (host_port);
    net_addr = htonl (host_addr);

    printf("主机端的端口号: %#X\n",host_port);
    printf("网络端的端口号：%#x\n",net_port);
    printf("主机端的IP地址: %#lx\n",host_addr);
    printf("网络端的IP地址: %#lx\n",net_addr);

    return 0;
}