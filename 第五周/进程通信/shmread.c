#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#define SHMKEY 75
typedef struct test
{
	int write;
	char buf[1];
}p;
int main()
{
	p *p1;
	int shm_create;
	shm_create=shmget(SHMKEY,1024,IPC_CREAT);
	if(shm_create==-1)
	{
		printf("接收方共享主存失败\n");
		exit(-1);
	}
	printf("接收方共享主存成功\n");
	p1=(p*)shmat(shm_create,NULL,0);
	printf("%s\n",p1->buf);
	return 0;
}
