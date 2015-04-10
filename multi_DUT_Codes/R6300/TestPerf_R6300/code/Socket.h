// Definition of the Socket class

#ifndef SOCKET_H
#define SOCKET_H
#include <string>      
#include <errno.h>       
#include <fcntl.h>     
#include <iostream>    
#include <sys/types.h> 
#include <netinet/in.h>  
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <sys/wait.h>    
#include <stdlib.h> 
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
                       
const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 10;
const int MAXRECV = 5120;
extern int symbol;


class Socket
{
	
public:
  Socket();
  virtual ~Socket();

public:
  int m_sock;
  bool vaildIf;
  sockaddr_in m_addr,client_addr; 
  // Definition of the Socket class

#ifndef SOCKET_H
#define SOCKET_H
#include <string>      
#include <errno.h>       
#include <fcntl.h>     
#include <iostream>    
#include <sys/types.h> 
#include <netinet/in.h>  
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <sys/wait.h>    
#include <stdlib.h> 
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
                       
const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 10;
const int MAXRECV = 5120;
extern int symbol;
class Socket
{
 public:
  Socket();
  virtual ~Socket();

  // Server initialization
  bool close();
  bool create();
  bool bind ( const int port );
  bool listen() const;
  bool accept ( Socket& ) const;

  // Client initialization
  bool connect ( const std::string host, const int port );

  // Data Transimission
  bool send ( const std::string ) const;
  int recv ( std::string& s ) const;
  int select_self();

  bool sendmsg(char *pData,int size);
  int recvmsg(char *pData,int size);
  void set_non_blocking ( const bool );

  bool is_valid() const { return m_sock != -1; }
  
 public:

  int m_sock;
  bool vaildIf;
  sockaddr_in m_addr,client_addr;


};


#endif

};


#endif
