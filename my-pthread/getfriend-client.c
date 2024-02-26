#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>


#define NAME_SIZE 20
#define BUF_SIZE 100
pthread_mutex_t mut;

int main()
{
    fputs("hi",stdout);
    return 0;
}