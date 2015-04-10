 // Implementation of the Socket class.


#include "Socket.h"

using namespace std;
int count1;
Socket::Socket() :
  m_sock ( -1 )
{

  memset ( &m_addr,
	   0,
	   sizeof ( m_addr ) );
  vaildIf = true;

}

Socket::~Socket()
{
//  if ( is_valid() )
  //  ::close ( m_sock );
}

bool Socket::close()
{
  if(is_valid())
     ::close(m_sock);
  vaildIf = false;
  return true;
}

bool Socket::create()
{
  m_sock = socket ( AF_INET,
		    SOCK_STREAM,
		    0 );

  if ( ! is_valid() )
	return false;


  // TIME_WAIT - argh
  int on = 1;
  if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
	return false;


  return true;

}



bool Socket::bind ( const int port )
{

  if ( ! is_valid() )
    {
    	printf("error");
      return false;
    }

  m_addr.sin_family = AF_INET;
  m_addr.sin_addr.s_addr = INADDR_ANY;
  m_addr.sin_port = htons ( port );

  int bind_return = ::bind ( m_sock,
			     ( struct sockaddr * ) &m_addr,
			     sizeof ( m_addr ) );

  
  if ( bind_return == -1 )
    {
    	printf("bind failure\n");
      return false;
    }
 printf("bind ok\n");
  return true;
}


bool Socket::listen() const
{
  if ( ! is_valid() )
    {
    	printf("error");
      return false;
    }

  int listen_return = ::listen ( m_sock, MAXCONNECTIONS );


  if ( listen_return == -1 )
    {
    printf("listen failure\n");
      return false;
    }

  return true;
}


bool Socket::accept ( Socket& new_socket ) const
{
  int addr_length = sizeof ( m_addr );
  printf("before accept\n");
   new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &client_addr, ( socklen_t * ) &addr_length );

  if ( new_socket.m_sock <= 0 )
  {
    printf("accept faulse\n");
    return false;
  }
  else
  {
    printf("accept ok\n");
    return true;
  }
}


bool Socket::send ( const std::string s ) const
{
  int status = ::send ( m_sock, s.c_str(), s.size(), MSG_NOSIGNAL );
  if ( status == -1 )
    {
      printf("send unsuccessfully\n");
      return false;
    }
  else
    {
      printf("send ok\n");
      return true;
    }
}

bool Socket::sendmsg(char *pData,int size)
{
	int status=::send(m_sock,pData,size,MSG_NOSIGNAL);
	if(status==-1)
	{
	  printf("send unsuccessfully"); 
	  return false;
	}
	else if(status==0) 
	{
		printf("Send finish!\n");
		return false;
	}
	else if(status>0)
	{
        printf("Send one message\n");
        return true;
	}
	return false;	
}

int Socket::recv ( std::string& s ) const
{
  char buf [ MAXRECV + 1 ];
  s = "";

  memset ( buf, 0, MAXRECV + 1 );

int status=::recv ( m_sock, buf, MAXRECV, 0 );
if ( status == -1 ) {
      //std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
       std::cout << "socket "<<m_sock<<" close\n";
       exit(1);
        return 0;
	}
else if ( status == 0 ) {
      return 0;
     }
     else
    {
      s = buf;
      symbol=1;
      count1++;
      std::cout <<count1<<"\n";
      return status;
    }
    
return 0;
}


int Socket::recvmsg(char* pData,int size)
{
   memset(pData,0,size);
   int status = ::recv(m_sock,pData,size,0);
   if(status==-1)
   {    
   	//printf("status: %d\n",status);
	return 0;
	
   }
   else if(status==0)
   {
	printf("status=0: %d\n",status);
	return 0;
   }
   else
   {
	//s=pData;
	printf("Recieve:%s\n",pData);
	printf("My status: %d\n",status);
        return(status);
    }
  
}


bool Socket::connect ( const std::string host, const int port )
{
  if ( ! is_valid() ) return false;

  m_addr.sin_family = AF_INET;
  m_addr.sin_port = htons ( port );

  int status = inet_pton ( AF_INET, host.c_str(), &m_addr.sin_addr );

  if ( errno == EAFNOSUPPORT ) return false;

  status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

  if ( status == 0 )
    return true;
  else
    return false;
}

void Socket::set_non_blocking ( const bool b )
{

  int opts;

  opts = fcntl ( m_sock,
		 F_GETFL );

  if ( opts < 0 )
    {
      return;
    }

  if ( b )
    opts = ( opts | O_NONBLOCK );
  else
    opts = ( opts & ~O_NONBLOCK );

  fcntl ( m_sock,
	  F_SETFL,opts );

}
int Socket::select_self()
{
    fd_set rfds;
    struct timeval tv;
    int retval;
    
    /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(m_sock, &rfds);
    
    tv.tv_sec = 300;
    tv.tv_usec = 0;
    retval = ::select(m_sock+1, &rfds, NULL, NULL, &tv);
    /* DonÜdìù rely on the value of tv now! */
    if (retval == -1)
    perror("select()");
    else if (retval)
    printf("Data is available now.\n");
    /* FD_ISSET(0, &rfds) will be true. */
    else
    printf("No data within five minutes.\n");
    
    return retval;	
}
