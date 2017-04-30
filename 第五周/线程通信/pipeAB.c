#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
int fd[2];
int pipe_create;
char *buf="hello zmw";
char buf1[50];
/*void *readpipe(void *arg)
{
	char pro=*(char*)arg;
	read(fd[0],buf1,strlen(buf));
	printf("%c read from pipe is: %s\n",pro,buf1);
	return 0;
}*/
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
	pthread_t child;
	int child_pthread;
	int wait_pthread;
	child_pthread=pthread_create(&child,NULL,writepipe,"A");
	if(child_pthread!=0)
	{
	printf("子线程创建失败\n");
	}
	wait_pthread=pthread_join(child,NULL);
	if(wait_pthread!=0)
	{
		printf("子线程还未完成\n");
	}
	printf("子线程已退出，在父线程下\n");
	read(fd[0],buf1,strlen(buf));
	printf("父线程读到的数据是%s\n",buf1);
	return 0;

}
