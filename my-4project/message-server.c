#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>

void error_handling(char *message);

int main(int argc,char *argv[])
{
    int sockfd_listen;//监听套接字
    int sockfd_connect;//连接套接字
    struct sockaddr_in ser_addr;//服务器端口+IP
    struct sockaddr_in cln_addr;//客户端端口+IP
    //int str_len;//传入字符串长度
    //socklen_t cln_addr_size;

    //给客户端的回复信息
    char msg1[]="你好，客户端";
	char msg2[]="这里是服务器";
	char msg3[]="很高兴见到你";
	char* str_arr[]={msg1, msg2, msg3};
	char read_buf[100];//读入缓冲区的大小，注意与TCP缓冲区区别

    if(argc!=2)
    {
        printf("你好，参数过多服务器启动失败\n");
        exit(1);
    }
    sockfd_listen=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd_listen==-1)
    {
        error_handling("服务器监听套接字创建失败\n");
    }
    //由于服务器端总是等待客户端来访问因此自己指定好端口进行了
    memset(&ser_addr,0,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(atoi(argv[1]));
    ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    //绑定地址信息与监听套接字
    if(bind(sockfd_listen,(struct sockaddr*)&ser_addr,sizeof(ser_addr))==-1)
    {
        error_handling("绑定失败");
    }
    //开启监听
    if(listen(sockfd_listen,5)==-1)
    {
        error_handling("监听失败");
    }
    //允许连接
    socklen_t cln_addr_len = sizeof(cln_addr);
	sockfd_connect = accept(sockfd_listen,(struct sockaddr*)&cln_addr,&cln_addr_len);
    if(sockfd_connect==-1)
    {
        error_handling("连接失败");
    }
    //开始发送信息逻辑
    for(int i=0;i<3;i++)
    {
        //需要写入的字符串的长度
        int str_len=strlen(str_arr[i])+1;
		write(sockfd_connect, (char*)(&str_len), 4);//含义是前面这四个字节是用来表示后续数据的长度的，不足四个字节补0，超过则采取其他的手段
        //写入字符串
		write(sockfd_connect, str_arr[i], str_len);
		
        //读取的字符串长度
		read(sockfd_connect, (char*)(&str_len), 4);
        //读取的字符串
		read(sockfd_connect, read_buf, str_len);
		puts(read_buf);
    }
    close(sockfd_listen);
    close(sockfd_connect);

    return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	int str_len, i;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char msg1[]="Hello client!";
	char msg2[]="I'm server.";
	char msg3[]="Nice to meet you.";
	char* str_arr[]={msg1, msg2, msg3};
	char read_buf[100];
	
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("bind() error"); 
	
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr);  
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");  
	
	for(i=0; i<3; i++)
	{
        //需要写入的字符串的长度
		str_len=strlen(str_arr[i])+1;
		write(clnt_sock, (char*)(&str_len), 4);
        //写入字符串
		write(clnt_sock, str_arr[i], str_len);

        //读取的字符串长度
		read(clnt_sock, (char*)(&str_len), 4);
		sleep(1);
        //读取的字符串
		read(clnt_sock, read_buf, str_len);
		sleep(1);
		puts(read_buf);
		sleep(1);
	}
	
	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
*/