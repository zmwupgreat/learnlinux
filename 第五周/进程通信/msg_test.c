#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#define MSGKEY 75
struct msgform
{
	long mytype;
	char mytext[1];
}msg;
int main()
{
	msg.mytext[0]='H';
	int msg_send;
	int msg_create;
	msg_create=msgget(MSGKEY,IPC_CREAT|0666);
	msg.mytype=2;
	if(msg_create==-1)
	{
		printf("消息队列创建失败\n");
		exit(-1);
	}
	printf("发送方消息队列创建成功\n");

	msg_send=msgsnd(msg_create,&msg,sizeof(msg.mytext),IPC_NOWAIT);
	if(msg_send==-1)
	{
		printf("发送失败\n");
		exit(-1);
	}
	printf("消息发送成功！\n");
	return 0;
}

