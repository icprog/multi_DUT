
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

int CTelnet::sendTelnetCmd(char *cmd,char *pData,int timeOut)
{		
   fd_set rfds;
    struct timeval tv;
    int retval;
    sprintf(sendData,"%s\n",cmd);
    printf("%s\n",sendData);
   
    		
    if(send(sockfd,sendData,strlen(sendData)+1,0)==-1)//socker send
    {
        perror("send");
        exit(1);
    } 
    else
    {
       printf("send ok!\n");
    }
     FD_ZERO(&rfds);
    FD_SET(sockfd, &rfds);
    printf("size:%d\n",sizeof(pData));
    printf("size1:%d\n",strlen(sendData)+1);
    /* Watch stdin (fd 0) to see when it has input. */
   
    tv.tv_sec = timeOut;
    tv.tv_usec = 0;
    retval = ::select(sockfd+1, &rfds, NULL, NULL, &tv);
    /* Donrely on the value of tv now! */
    if (retval == -1)
    	perror("select()");
    else if (retval)
    	printf("Data is available now.\n");
    /* FD_ISSET(0, &rfds) will be true. */
    else
    	printf("No data within one second.\n");
   if(retval)
{ 
   	usleep(500000);
   	int status = ::recv(sockfd,pData,1000,0);
   if(status==-1)
   {    
   	printf("status: %d\n",status);
	return 0;
	
   }
   else if(status==0)
   {
	printf("status=0: %d\n",status);
	return 0;
   }
   else
   {
	printf("Recieve:%s\n",pData);
	printf("My status: %d\n",status);
       return(status);
    }
}
    return 0;
}
int CTelnet::getTelnetAction(char *pData,int timeOut)
{		
   fd_set rfds;
    struct timeval tv;
    int retval;
 
     FD_ZERO(&rfds);
    FD_SET(sockfd, &rfds);
    printf("size:%d\n",sizeof(pData));
    printf("size1:%d\n",strlen(sendData)+1);
    /* Watch stdin (fd 0) to see when it has input. */
   
    tv.tv_sec = timeOut;
    tv.tv_usec = 0;
    retval = ::select(sockfd+1, &rfds, NULL, NULL, &tv);
    /* Don rely on the value of tv now! */
    if (retval == -1)
    	perror("select()");
    else if (retval)
    	printf("Data is available now.\n");
    /* FD_ISSET(0, &rfds) will be true. */
    else
    	printf("No data within %d seconds.\n",timeOut);
   if(retval)
{ 
   	usleep(500000);
   	int status = ::recv(sockfd,pData,1000,0);
   if(status==-1)
   {    
   	printf("status: %d\n",status);
	return 0;
	
   }
   else if(status==0)
   {
	printf("status=0: %d\n",status);
	return 0;
   }
   else
   {
	//printf("Recieve:%s\n",pData);
	printf("My status: %d\n",status);
       return(status);
    }
}
    return 0;
}
