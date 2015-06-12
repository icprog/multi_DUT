#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>



#define MYPORT    12000		/* 监听端口 */
#define BACKLOG 10 		/* listen的请求接收队列长度 */

/*
	Led action parser
*/
bool ledAction(char *para)
{
   Led Red(RED),Yellow(YELLOW),Green(GREEN);
   if(strcmp(para,"red_on")==0)
     Red.On();
   else if(strcmp(para,"red_off")==0)
     Red.Off();
   else if(strcmp(para,"red_blink")==0)
     Red.Blink();
   else if(strcmp(para,"green_on")==0)
     Green.On();
   else if(strcmp(para,"green_off")==0)
     Green.Off();
   else if(strcmp(para,"green_blink")==0)
     Green.Blink();
   else if(strcmp(para,"yellow_on")==0)
     Yellow.On();
   else if(strcmp(para,"yellow_off")==0)
     Yellow.Off();
   else if(strcmp(para,"yellow_blink")==0)
     Yellow.Blink();
   else
     return false;
   return true;
}    


/*
	main function(its' a test case)
*/
int main()
{
	int sockfd, new_fd; 		/* 监听端口，数据端口 */
	struct sockaddr_in my_addr; 	/* 自身的地址信息 */
	struct sockaddr_in their_addr; 	/* 连接对方的地址信息 */
	int sin_size;
	fd_set rfds;
	int retval;
	char led_sign;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
	perror("socket");
	exit(1);
	}

	my_addr.sin_family = AF_INET; 
	my_addr.sin_port = htons(MYPORT); 		/* 网络字节顺序 */
	my_addr.sin_addr.s_addr = INADDR_ANY; 	/* 自动填本机IP */
	bzero(&(my_addr.sin_zero), 8); 		/* 其余部分置0 */

	if  (bind(sockfd, (struct sockaddr *)&my_addr, 
			sizeof(struct sockaddr)) == -1) 
	{
		perror("bind");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) 
	{
		perror("listen");
		exit(1);
	}

	while(1)
	{ 	
		/* 主循环 */
		FD_ZERO(&rfds);
		FD_SET(sockfd,&rfds);
		char *p=NULL;
		retval=select(sockfd+1,&rfds,NULL,NULL,NULL);//select timeout
		if(retval==-1)
		{
			perror("select");
			exit(1);
		}
		sin_size = sizeof(struct sockaddr_in);
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr,
								(socklen_t *)&sin_size);
		if(new_fd== -1)
		{
			perror("accept");
			continue;
		}
		printf("sever:got connection from %s\n", inet_ntoa(their_addr.sin_addr));

		if (!fork()) 
		{       char *delm=" ";
			if(recv(new_fd,buf,MAXDATASIZE,0)==-1)
			{
				perror("recv");
				exit(1);
			}
			sscanf(buf,"%c",&led_sign);
			printf("buf:%s\n",buf);
			if(!ledAction(strtok(buf,delm)))
			printf("sign fault\n");
			while(p=strtok(NULL,delm))
			{
			  if(!ledAction(p))
			  printf("sign fault\n");
			}
			close(new_fd);// close thread
			exit(0);
		}
		close(new_fd); 	//close socket
		while(waitpid(-1,NULL,WNOHANG) > 0);
	}
	return 0;
}
    

