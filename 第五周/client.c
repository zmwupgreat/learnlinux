#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>
#include<sys/un.h>
#define LOCALADDR "/home/zmw/文档/第五周/1.socket"
int main()
{
	int ret;
	int client_fd;
	int server_len;
	int client_connect;
	struct sockaddr_un server_addr;
	char *buffer="hello";
	char buffer1[1024];
	client_fd=socket(PF_UNIX,SOCK_STREAM,0);
	server_addr.sun_family=PF_UNIX;
	strcpy(server_addr.sun_path,LOCALADDR);
	server_len=sizeof(server_addr);

	client_connect=connect(client_fd,(struct sockaddr *)&server_addr,server_len);
      
	if(client_connect<0)
	{
		printf("connect失败！\n");
		return -1;
	}
        printf("连接成功\n");
while(1)
{
	printf("please input:");
	gets(buffer1);
	write(client_fd,buffer1,strlen(buffer1));
	memset(buffer1,'\0',1024);
	ret=read(client_fd,buffer1,1024);
	buffer1[ret]='\0';
        printf("from server:%s\n",buffer1);
	memset(buffer1,'\0',1024);
}
return 0;
}
