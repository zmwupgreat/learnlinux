#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>
int main()
{
	int client_fd;
	int server_len;
	int client_connect;
	struct sockaddr_in server_addr;
	char *buffer="hello zmw";
	char buffer1[50];
	client_fd=socket(AF_INET,SOCK_STREAM,0);
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=9734;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_len=sizeof(server_addr);

	
	
	client_connect=connect(client_fd,(struct sockaddr *)&server_addr,server_len);
      
	if(client_connect<0)
	{
		printf("connect失败！\n");
		return -1;
	}
        printf("连接成功\n");
	write(client_fd,buffer,strlen(buffer));
	read(client_fd,buffer1,50);
        printf("from server:%s\n",buffer1);
	close(client_fd);
	close(client_fd);
	exit(0);
}
