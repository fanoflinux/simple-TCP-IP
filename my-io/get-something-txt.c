#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    FILE *my_file;
    char buffer[1024];
    my_file=fopen("test.txt","a+");
    if(my_file==NULL)
    {
        fputs("打开失败！",stdout);
    }
    else
    {
        if(fgets(buffer,sizeof(buffer),stdin)!=NULL)
        {
            fputs(buffer,my_file);
        }
    }
    fclose(my_file);
    printf("任务已完成！\n");
    return 0;
}