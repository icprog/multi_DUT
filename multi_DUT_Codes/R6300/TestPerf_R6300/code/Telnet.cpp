
#include "Telnet.h"

#define		N		16
#define		PORT 	23


CTelnet::CTelnet(char *ipAddr)
{
	memset(ipAddress,0,sizeof(ipAddress));
	strcpy(ipAddress,ipAddr);
	
	if ((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) //set up socket	
	{
        	perror("socket");
        	exit(1);
    	} 
	
    	their_addr.sin_family = AF_INET;
    	their_addr.sin_port = htons(PORT);
        their_addr.sin_addr.s_addr =inet_addr(ipAddress);
    	bzero(&(their_addr.sin_zero), 8);
	
	if(connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr))==-1)
	{
	    perror("connect");
	    exit(1);
	}//socket connect
	else
	{
            printf("connect ok!\n");
        }
}

CTelnet::~CTelnet()
{
	close(sockfd);  //close socket 
}
