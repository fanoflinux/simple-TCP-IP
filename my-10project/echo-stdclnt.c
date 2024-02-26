#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc,char* argv[])
{
    int sock;
    struct sockaddr_in adr;
    char message[BUF_SIZE];
    FILE *readfp;
    FILE *writefp;
    int str_len;

    if(argc!=3)
    {
        printf("Usage ()%s<IP> <port>\n",argv[0]);
        exit(1);
    }

    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock==-1)
    {error_handling("socket() error");}
    memset(&adr,0,sizeof(adr));
    adr.sin_family=AF_INET;
    adr.sin_addr.s_addr=inet_addr(argv[1]);
    adr.sin_port=htons(atoi(argv[2]));
    if(connect(sock,(struct sockaddr*)&adr,sizeof(adr))==-1)
    {error_handling("connect() error");}
    else{printf("connected!\n");}
    readfp=fdopen(sock,"r");
    writefp=fdopen(sock,"w");
    while(1)
    {
        fputs("INPUT MESSAGE (Q IS QUIT)",stdout);
        fgets(message,BUF_SIZE,stdin);
        if(!strcmp(message,"q\n")||(!strcmp(message,"Q\n")))
        break;
        fputs(message,writefp);
        fflush(writefp);
        fgets(message,BUF_SIZE,readfp);
        printf("MESSAGE FROM SERVER IS :%s",message);
    }
    fclose(writefp);
    fclose(readfp);
    return 0;
}
void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}