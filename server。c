//这是服务器端的代码内容
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>



int main()
{
    //1、创建用于监听的套接字
    int fd_listen = socket(AF_INET,SOCK_STREAM,0);
    if(fd_listen ==-1)
    {
        perror("socket");
        return -1;
    }
    //2、将监听套接字与本地的端口及ip地址进行绑定
    struct sockaddr_in saddr;//声明绑定套接字的函数
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(10000);//最好指定5000以上的端口，基本不会被占用
    saddr.sin_addr.s_addr = INADDR_ANY;//自动匹配网卡的ip地址
    int ret = bind(fd_listen,(struct sockaddr*) &saddr,sizeof(saddr));
    if(ret == -1)
    {
        perror("bind");
        return -1;
    }
    //3、开启监听
    ret = listen(fd_listen,128);
    if(ret == -1)
    {
        perror("listen");
        return -1;
    }
    //4、阻塞并等待客户端连接,建立了连接将会得到一个用于通信的套接字
    struct sockaddr_in cadder;
    int cadderlen = sizeof(cadder);
    int fd_connect = accept(fd_listen,(struct sockaddr*)& cadder,&cadderlen);
    if(fd_connect == -1)
    {
        perror("connect");
        return -1;
    }
    //连接成功打印客户端的端口与ip信息
    char ip[32];
    printf("客户端的IP:%s;客户端的端口号为：%d\n",
    inet_ntop(AF_INET,&cadder.sin_addr,ip,sizeof(ip)),
    ntohs(cadder.sin_port));
    //5、进行通信
    while(1)
    {
        //建立一个缓冲区对客户端传到服务器端的数据进行存储
        char buffer_read[1024];
        int len = recv(fd_connect,buffer_read,sizeof(buffer_read),0);
        if(len > 0)
        {
            printf("客户端发送的数据为:%s\n",buffer_read);
            send(fd_connect,buffer_read,len,0);
        }
        else if(len == 0)
        {
            printf("客户端已经断开了连接\n");
            break;
        }
        else
        {
            perror("recv");
            break;
        }
    }
    //关闭通信描述符
    close(fd_listen);
    close(fd_connect);
    
    return 0;
}
