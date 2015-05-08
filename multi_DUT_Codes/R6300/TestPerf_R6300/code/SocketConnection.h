// Definition of the Socket server
#ifndef SOCKET_CONNECTION_H
#define SOCKET_CONNECTION_H
#include"Socket.h"
#include<iostream>
#include <semaphore.h>
#include<string>
#include<list>

using namespace std;
	typedef struct DotSocBuffTag
{
	unsigned long Len;
	char Data[3000];
}DOT_SOC_BUF;


class CSocketConnection
{
public:
	/*structor function*/
	CSocketConnection();
	
	/*destructor function*/
	virtual ~CSocketConnection();

public:
	/*create connection thread */
	bool Connection();
	
	/*send data to connection socket*/
	bool socketSend(char* sendbuffer);
	
	/*get the connection request socket list */
	int GetRevList(char *p, int size);
	
	/*define the data recive from where*/
	unsigned long recive_from(char *pData, unsigned long size);
	
	/*insert request socket to the respone list*/
	int InsertRevList(DOT_SOC_BUF *p);

public:
	Socket revSocket,SocketSer;;
	int m_sock;
	int ensureSymbol;
	sockaddr_in m_addr;
	sem_t hRevListMutex;
	list<DOT_SOC_BUF> RevList;
	

};

#endif
