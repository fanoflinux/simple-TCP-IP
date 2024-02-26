#include<stdio.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
    char *addr1 = "1.2.3.4";
    char *addr2="1.2.3.257";

    unsigned long conv_addr = inet_addr(addr1);
    if(conv_addr==INADDR_ANY)
        printf("ERROR OCCURED! \n");
    else
        printf("NetWork ordered Iteger Addr:%#lx \n",conv_addr);
    conv_addr = inet_addr(addr2);
    if(conv_addr==INADDR_ANY)
        printf("ERROR OCCURED! \n");
    else
        printf("NetWork ordered Iteger Addr:%#lx \n",conv_addr);
    return 0;
}