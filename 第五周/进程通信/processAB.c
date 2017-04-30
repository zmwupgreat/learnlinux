#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	pid_t PA,PB;
	PA=fork();
	if(PA<0)
	{
		printf("PA进程创建失败\n");
		exit(-1);
	}
	else if(PA==0)
	{
		printf("在子进程PA中\n");
		sleep(3);
		exit(0);
	}
	else
	{
		if(PA!=wait(NULL))
		{
			printf("子进程PA还没退出\n");
		}
		printf("子进程PA已退出\n");
		PB=fork();
		if(PB<0)
		{
			printf("子进程PB创建失败\n");
			exit(-1);
		}
		else if(PB==0)
		{
			printf("在子进程PB中\n");
			sleep(3);
			exit(0);
		}
		else
		{
			if(PB!=wait(NULL))
			{
				printf("子进程PB还没退出\n");
			}
			printf("子进程PB已退出\n");
			printf("在父进程下\n");
		}
	}
	return 0;
}
