#include <stdio.h>	
#include <stdlib.h> 
#include <errno.h>	
#include <string.h> 
#include <sys/time.h>	
#include <netdb.h>	
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class CTelnet
{
public:
	fd_set rfds;
	int sockfd;
    struct sockaddr_in their_addr;
    char sendData[300];
    char ipAddress[20];

		
public:
	CTelnet(char *ipAddr);
	~CTelnet();
	
};
