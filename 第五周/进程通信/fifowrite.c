#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#define TMPFIFO "/home/zmw/文档/第五周/进程通信/TMPFIFO"
int main(int argc,char *argv[])
{
	int fifo_fd;
	int fifo_create=mkfifo(TMPFIFO,O_CREAT|O_EXCL);
	int pid=getpid();
	int fifo_write;
	char *buf="hello zmw";
	if(fifo_create!=0)
		{
			printf("命名管道创建失败！\n");
			return -1;
		}
		printf("进程%d正在使用命名管道",pid);
	fifo_fd=open(TMPFIFO,O_WRONLY);
	if(fifo_fd<0)
	{
		printf("进程%d打开管道失败！\n",pid);
		return -1;
	}
	else
	{
	fifo_write=write(fifo_fd,buf,strlen(buf));
		if(fifo_write<0)
		{
		printf("进程%d写入失败！\n",pid);
		return -1;
		}
		printf("进程%d写入成功！\n",pid);
	close(fifo_fd);
	
	}
}
