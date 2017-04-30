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
	int fifo_read;
	int pid=getpid();
	char buf[100];
	fifo_fd=open(TMPFIFO,O_RDONLY);
	if(fifo_fd<0)
	{
		printf("进程%d打开管道失败！\n",pid);
		return -1;
	}
	else
	{
		printf("进程%d正在使用管道读取数据！\n",pid);
		fifo_read=read(fifo_fd,buf,100);
		if(fifo_read<0)
		{
			printf("进程%d读取数据失败！\n",pid);
			return -1;
		}
		printf("进程%d读取成功！\n",pid);
		printf("%s\n",buf);
		close(fifo_fd);
	}

}
