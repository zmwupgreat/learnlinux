#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<unistd.h>
int main()
{
	int server_fd,client_fd;
	int server_len,client_len;
	int server_bind;
	int server_listen;
	struct sockaddr_in saddr_s;
	struct sockaddr_in saddr_c;
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_fd<0)
	{
		printf("socket创建失败！\n");
		return -1;
	}
	saddr_s.sin_family=AF_INET;
	saddr_s.sin_port=9734;
	saddr_s.sin_addr.s_addr=INADDR_ANY;
	server_len=sizeof(saddr_s);
	server_bind=bind(server_fd,(struct sockaddr *)&saddr_s,server_len);
	if(server_bind<0)
	{
		printf("bind绑定失败！\n");
		return -1;
	}
	server_listen=listen(server_fd,3);
	if(server_listen<0)
	{
		printf("listen建立队列失败！\n");
		return -1;
	}
	while(1)
	{
		printf("等待客户请求到达......\n");
		int server_accept;
		client_len=sizeof(saddr_c);
		client_fd=accept(server_fd,(struct sockaddr *)&saddr_c,&client_len);
		if(client_fd<0)
		{
			printf("accept建立连接失败！\n");
			return -1;
		}
		printf("连接成功\n");
		char *add="recieved";
		char buf[50];
		read(client_fd,buf,50);
		printf("server read %s\n",buf);
		strcat(buf,add);
		printf("server add %s\n",buf);
		write(client_fd,buf,50);
		close(client_fd);
	}
	return 0;
}
//server.c

