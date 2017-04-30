#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
int fd[2];
int pipe_create;
char *buf="hello zmw";
char buf1[50];
void *readpipe(void *arg)
{
	char pro=*(char*)arg;
	read(fd[0],buf1,strlen(buf));
	printf("%c read from pipe is: %s\n",pro,buf1);
	return 0;
}
void *writepipe(void *arg)
{
	char pro=*(char*)arg;
	write(fd[1],buf,strlen(buf));
	printf("childthread%c write to pipe %s\n",pro,buf);
	return 0;
}
int main()
{
	pipe_create=pipe(fd);
	pthread_t childA;
	int child_pthreadA;
	int wait_pthreadA;
	child_pthreadA=pthread_create(&childA,NULL,writepipe,"A");
	if(child_pthreadA!=0)
	{
	printf("子线程A创建失败\n");
	}
	wait_pthreadA=pthread_join(childA,NULL);
	if(wait_pthreadA!=0)
	{
		printf("子线程A还未完成\n");
	}
	printf("子线程A已退出，在父线程下\n");
	pthread_t childB;
	int child_pthreadB;
	int wait_pthreadB;
	child_pthreadB=pthread_create(&childB,NULL,readpipe,"B");
	if(child_pthreadB!=0)
	{
		printf("子线程B创建失败\n");
	}
	wait_pthreadB=pthread_join(childB,NULL);
	if(wait_pthreadB!=0)
	{
		printf("子线程B还未完成\n");
	}
	printf("子线程B已退出\n");
	
	return 0;

}
