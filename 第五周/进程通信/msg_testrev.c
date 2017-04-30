#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#define MSGKEY 75
struct msgform
{
	long mytype;
	char mytext[10];
}msg;
int main()
{
	int msg_create;
	int msg_rev;
	msg_create=msgget(MSGKEY,IPC_CREAT|0666);
	if(msg_create==-1)
	{
		printf("消息队列创建失败！\n");
		exit(-1);
	}
	else
	{
	printf("接收方消息队列创建成功\n");
	msg_rev=msgrcv(msg_create,&msg,4,2,0);
	if(msg_rev==-1)
	{
		printf("消息接收失败\n");
	exit(-1);
	}
	else
	{printf("消息接收成功!\n");
	printf("%s\n",msg.mytext);
	}
	}
	return 0;
}
