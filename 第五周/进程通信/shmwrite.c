#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<unistd.h>
#define SHMKEY 75
typedef struct test
{
	int write;
	char buf[1];
}p;
int main()
{
	p *p1;
	char tmp='H';
	int shm_create;
	int shm_del;
	shm_create=shmget(SHMKEY,1024,IPC_CREAT);
	if(shm_create==-1)
	{
		printf("共享主存失败\n");
		exit(-1);
	}
	printf("共享主存成功\n");
	p1=(p*)shmat(shm_create,NULL,0);
	memcpy((*(p1)).buf,&tmp,1);
	p1->write=1;
	printf("写入成功\n");
	
	return 0;

}
