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
	CSocketConnection();
	virtual ~CSocketConnection();

public:
	bool Connection();
	bool socketSend(char* sendbuffer);
	int GetRevList(char *p, int size);
	unsigned long recive_from(char *pData, unsigned long size);
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
