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
#define SIZE 1024
#define SIZEADD 2048
#define LOCALADDR "/home/zmw/文档/第五周/1.socket"
struct sockaddr_un sock_server;
struct sockaddr_un sock_client;
int fds[64];
int main()
{	int server_fd,client_fd;
	int server_len=sizeof(sock_server);
	int client_len=sizeof(sock_client);
	int sock_bind;
	int sock_listen;
	char buf[SIZEADD];	
	char *add="hello zmw";
	int yes=1;
	server_fd=socket(AF_UNIX,SOCK_STREAM,0);//创建域套接字
	if(server_fd<0)
	{
		printf("socket创建失败!\n");
		exit(-1);
	}	
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,&yes, sizeof(int)) == -1) {  
        perror("setsockopt");  
        exit(1);  
    }  
     
	sock_server.sun_family=AF_UNIX;//设置结构体参数
	strcpy(sock_server.sun_path,LOCALADDR);
	sock_bind=bind(server_fd,(struct sockaddr *)&sock_server,server_len);//绑定域套接字
	if(sock_bind!=0)
	{
		printf("bind绑定失败!\n");
		exit(-1);
	}
	sock_listen=listen(server_fd,5);//设置监听
	if(sock_listen<0)
	{
		printf("监听创建失败！\n");
		exit(-1);
	}
	while(1)
	{
		fd_set read_t;//需要监视的可读文件描述符集合
		fd_set write_t;//需要监视的可写文件描述符集合
		int fds_max;//描述符中最大的
		int num=sizeof(fds)/sizeof(fds[0]);
		for(int i=0;i<num;i++)
		{
			fds[i]=-1;//初始化描述符集合中的所有描述符
		}		
		fds[0]=server_fd;//设置第一个描述符为域套接字服务器描述符
		fds_max=server_fd;//设置初始描述符最大值;
		struct timeval times;//用于描述一段时间长度，在这个时间内，需要监视的描述符没有时间发生则返回0
		while(1)
		{
			FD_ZERO(&read_t);
			FD_ZERO(&write_t);//因为这两个参数为输入型参数，一直会改变，每次循环都需要初始化
			FD_SET(server_fd,&read_t);//把服务器描述符置入可读文件描述符集合
			times.tv_sec=10;//设置10秒
			times.tv_usec=0;//设置毫秒为0
			for(int i=1;i<num;i++)//在select之前把所有的文件描述符都设置成读事件
			{
				if(fds[i]>0)
				{
					FD_SET(fds[i],&read_t);
					if(fds[i]>fds_max)
					{
						fds_max=fds[i];//设置最大描述符				
					}
				}
			}
			int select_t;
			select_t=select(fds_max+1,&read_t,&write_t,NULL,&times);//调用select函数
			switch(select_t)
			{
				case 0:
					printf("time out ...\n");
					break;
				case -1:
					printf("select失败!\n");
					break;
				default:
					for(int i=0;i<num;i++)
					{
						if((fds[i]==server_fd)&&(FD_ISSET(fds[i],&read_t)))//测试是否可读文件
							{
				       printf("正在等待连接....\n");								
				client_fd=accept(server_fd,(struct sockaddr *)&sock_client,&client_len);//等待连接请求
								
								if(client_fd<0)
								{
									printf("accept失败！\n");
									continue;	
								}
								printf("新链接创建，描述符为%d\n",client_fd);
								for(int i=0;i<num;i++)
								{
									if(fds[i]<0)
									{
										fds[i]=client_fd;
										FD_SET(fds[i],&write_t);
										break;
									}
								}
								if(i==num-1)
								{
									printf("文件描述符已满，请关闭部分链接\n");	
								}
							}
						else if((fds[i]>0)&&(FD_ISSET(fds[i],&read_t)))//检查该描述符是不是在读中，若在则读
						{	
							memset(buf,'\0',SIZE);
							read(fds[i],buf,SIZE);
							printf("接收到的数据为%s\n",buf);
							strcat(buf,add);
							printf("add后的数据为%s\n",buf);
							write(fds[i],buf,80);
							//memset(buf,'\0',SIZEADD);
							
						}
					}break;
			}
		}
	}

}
//server.c 参考http://10704527.blog.51cto.com/10694527/1782636

