// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/socket.h>

// #define BUF_SIZE 30
// void error_handling(char *message);
// void read_routine(int sock, char *buf);
// void write_routine(int sock, char *buf);

// int main(int argc, char *argv[])
// {
//     int sock;
//     pid_t pid;
//     char buf[BUF_SIZE];
//     struct sockaddr_in serv_adr;
//     if (argc != 3)
//     {
//         printf("Usage : %s <IP> <port>\n", argv[0]);
//         exit(1);
//     }
//     sock = socket(PF_INET, SOCK_STREAM, 0);
//     memset(&serv_adr, 0, sizeof(serv_adr));
//     serv_adr.sin_family = AF_INET;
//     serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
//     serv_adr.sin_port = htons(atoi(argv[2]));

//     if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
//         error_handling("connect() error!");

//     pid = fork();
//     if (pid == 0)
//         write_routine(sock, buf);
//     else
//         read_routine(sock, buf);

//     close(sock);
//     return 0;
// }

// void read_routine(int sock, char *buf)
// {
//     while (1)
//     {
//         int str_len = read(sock, buf, BUF_SIZE);
//         if (str_len == 0)
//             return;

//         buf[str_len] = 0;
//         printf("Message from server: %s", buf);
//     }
// }
// void write_routine(int sock, char *buf)
// {
//     while (1)
//     {
//         fgets(buf, BUF_SIZE, stdin);
//         if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
//         {
//             shutdown(sock, SHUT_WR); //向服务器端传递 EOF,因为fork函数复制了文件描述度，所以通过1次close调用不够
//             return;
//         }
//         write(sock, buf, strlen(buf));
//     }
// }

// void error_handling(char *message)
// {
//     fputs(message, stderr);
//     fputc('\n', stderr);
//     exit(1);
// }



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_MAXSIZE 1024
void error_handling(char *message);

int main(int argc,char* argv[])
{
    int clnt_sock;
    char message[BUF_MAXSIZE];
    int str_len;//
    struct sockaddr_in serv_adr;//创建服务器的端口+IP地址信息
    if(argc!=3)
    {
        printf("Usage : %s <IP> <prot>\n",argv[0]);
        exit(1);
    }

    clnt_sock=socket(AF_INET,SOCK_STREAM,0);//创建套接字
    if(clnt_sock==-1)
    {
        error_handling("创建客户端套接字失败\n");
    }
    memset(&serv_adr,0,sizeof(serv_adr));//将客户端的相关消息置为初始值
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    if(connect(clnt_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
    {
        error_handling("客户端连接失败\n");
    }
    else
    {
        puts("正在连接服务器");
    }
    while(1)
    {
        fputs("输入Q停止访问服务器",stdout);
        fgets(message,BUF_MAXSIZE,stdin);
        if(!strcmp(message,"q\n")||!strcmp(message,"Q\n"))
            break;
        write(clnt_sock,message,strlen(message));
        str_len=read(clnt_sock,message,BUF_MAXSIZE-1);
        message[str_len]=0;
        printf("服务器端发来的消息为:%s",message);
    }
    close(clnt_sock);
    return 0;
}
void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}