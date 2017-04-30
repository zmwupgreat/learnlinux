#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<unistd.h>
#include<sys/un.h>
#include<sys/time.h>
#include<sys/select.h>
#define LOCALADDR "/home/zmw/文档/第五周/1.socket"
int main()
{
	int fd[5];
	int count;
	int isREUSE=1;
	int sock_opt;
	int server_fd,client_fd;
	int server_len,client_len;
	int server_bind;
	int server_listen;
	struct sockaddr_un saddr_s;
	struct sockaddr_un saddr_c;
	int rdsocketlen=0;	

 	server_fd=socket(PF_UNIX,SOCK_STREAM,0);
	if(server_fd==-1)
	{
		printf("socket创建失败！\n");
		return -1;
	}
	sock_opt=setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&isREUSE,sizeof(isREUSE));//允许在同一个端口启动服务器的多个实例
	if(sock_opt==-1)
	{
		printf("setsockopt失败\n");
		exit(-1);
	}

	saddr_s.sun_family=PF_UNIX;
	strcpy(saddr_s.sun_path,LOCALADDR);
	server_len=sizeof(saddr_s);
	server_bind=bind(server_fd,(struct sockaddr *)&saddr_s,server_len);
	if(server_bind!=0)
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
	fd_set readfds;
	struct timeval time_a;
	int maxfd;
	maxfd=server_fd;
	count=0;
/*	while(1)
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
	}*/
char *add="recieved";
char buf[50];
	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(server_fd,&readfds);
		time_a.sec=10;
		time_a.usec=0;
		maxfd=server_fd;
		for(int i=0;i<count;i++)
		{
			FD_SET(fd[i],&readfds);
			if(fd[i]>maxfd)
			{
				maxfd=fd[i];
			}
		}
		int select_a=select(maxfd+1,&readfds,NULL,NULL,&time_a);
		if(select_a<0)
		{
			printf("select失败\n");
		}
		if(select_a==0)
		{
			continue;
		}
	for(int j=0;j<count;j++)
	{
		if(FD_ISSET(fd[j],&readfds))
		{
			rdsocketlen=read(select[j],buf,50);
			printf("server read %s\n",buf);
			strcat(buf,add);
			write(select[j],buf,50);
			if(rdsocketlen>0)
			{
			printf("server add %s\n",buf);
			}
		}
	
	}
	

	}
	return 0;
}
//server.c

