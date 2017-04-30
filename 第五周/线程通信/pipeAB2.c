#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>
#include<sys/wait.h>
#include<fcntl.h>
pthread_mutex_t lock_mutex;
char *buf="hello zmw";
sem_t empty,full;
char buf1[50];
int fileopen;
void *readfile(void *arg)
{
	sem_wait(&empty);
	pthread_mutex_lock(&lock_mutex);
	char pro=*(char*)arg;
	read(fileopen,buf1,100);
	printf("%c read from pipe is: %s\n",pro,buf1);
	sem_post(&full);
	pthread_mutex_unlock(&lock_mutex);
	return 0;
}
void *writefile(void *arg)
{
	sem_wait(&full);
	pthread_mutex_lock(&lock_mutex);
	char pro=*(char*)arg;
	write(fileopen,buf,100);
	printf("childthread%c write to pipe %s\n",pro,buf);
	sem_post(&empty);
	pthread_mutex_unlock(&lock_mutex);
	return 0;
}
int main()
{
	fileopen=open("/home/zmw/文档/第五周/test.txt",O_RDWR|O_CREAT);
	pthread_t childA;
	pthread_t childB;
	int child_pthreadA;
	int child_pthreadB;
	sem_init(&empty,0,2);
	sem_init(&full,0,0);
	child_pthreadA=pthread_create(&childA,NULL,writefile,"A");
	if(child_pthreadA!=0)
	{
	printf("A线程创建失败\n");
	}
	if(child_pthreadB!=0)
	{
	printf("B线程创建失败\n");
	}
	printf("线程创建成功！\n");
	child_pthreadB=pthread_create(&childB,NULL,readfile,"B");
	pthread_join(childA,NULL);
	pthread_join(childB,NULL);
	return 0;

}
