#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>

#define BUF_SIZE 1024
void error_handling(char *message);


int main(int argc,char *argv[])
{
    int ser_sock,cln_sock;
    char message[BUF_SIZE];
    struct sockaddr_in ser_adr,cln_adr;
    int str_len;
    FILE* readfp;
    FILE* writefp;
    if(argc!=2)
    {
        printf("Usage:%s<prot>:\n",argv[0]);
        exit(1);
    }
    ser_sock=socket(AF_INET,SOCK_STREAM,0);
    if(ser_sock==-1)
    {
        error_handling("socker() error");
    }
    memset(&ser_adr,0,sizeof(ser_adr));
    ser_adr.sin_family=AF_INET;
    ser_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    ser_adr.sin_port=htons(atoi(argv[1]));

    if(bind(ser_sock,(struct sockaddr*)&ser_adr,sizeof(ser_adr))==-1)
    {error_handling("bind() error");}
    if(listen(ser_sock,5)==-1)
    {error_handling("listen() error");}
    socklen_t cln_adr_sz=sizeof(cln_adr);

    for(int i=0;i<5;i++)
    {
        cln_sock=accept(ser_sock,(struct sockaddr*)&cln_adr,&cln_adr_sz);
        if(cln_sock==-1)
        {error_handling("accept() error");}
        else{printf("Connect client %d\n",i+=1);}
        readfp=fdopen(cln_sock,"r");
        writefp=fdopen(cln_sock,"w");
        while(!feof(readfp))
        {
            fgets(message,BUF_SIZE,readfp);
            fputs(message,writefp);
            fflush(writefp);
        }
        fclose(readfp);
        fclose(writefp);
    }
    close(cln_sock);
    return 0;
}
void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}