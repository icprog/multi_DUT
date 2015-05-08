#include "SocketConnection.h"
 
#include <pthread.h>
#include <semaphore.h>

int ConnectionIf;
CSocketConnection *psd;
extern int TestEnd;
extern bool gThreadExitFlag;
extern pthread_t TestThreadID;

CSocketConnection::CSocketConnection()
{
	int ret;
	ret=sem_init(&hRevListMutex,0,1);
}

CSocketConnection::~CSocketConnection()
{

}

unsigned long CSocketConnection:: recive_from(char *pData, unsigned long size)
{         
        int selectRet = revSocket.select_self();
        if(selectRet>0)
        {
        	int  bytesRecv=revSocket.recvmsg(pData,size);
        	printf("return select\n");
        	return bytesRecv;
        }
        else if(selectRet==0)
        {
        	printf("return no select\n");
        	return -1;
        	
        }
        else
        	return -2;

	
}

int CSocketConnection::InsertRevList(DOT_SOC_BUF *p)
{
	sem_wait(&hRevListMutex);
	RevList.push_back(*p);
	sem_post(&hRevListMutex);
	return 1;
}
bool CSocketConnection::socketSend(char* sendbuffer)
{
	int duration=0;
    struct timeval tvStart,tvEnd;
	ensureSymbol=0;
	bool sendIf= psd->revSocket.sendmsg(sendbuffer,strlen(sendbuffer));
	gettimeofday(&tvStart,NULL);
	if(!sendIf)
	{
		return false;
	}
	
	while((ensureSymbol==0)&&(duration<10))
	{
		usleep(1);
		gettimeofday(&tvEnd,NULL);
	    duration=tvEnd.tv_sec-tvStart.tv_sec;
	}
    if(duration>=10)
    {
        ensureSymbol=1;
        
    }
    
	return true;
}
bool CSocketConnection::Connection()
{
	SocketSer.create();
	SocketSer.bind(10000);
	pthread_t ConnectionID;

	if(!pthread_create(&ConnectionID,NULL,(void* (*) (void*))MainConnectionThread,this))
	    return true;
	else
	    return false;
}
int CSocketConnection::GetRevList(char *p, int size)
{
	DOT_SOC_BUF msgtemp;

	sem_wait(&hRevListMutex);
	if (!RevList.empty())
	{
		msgtemp=RevList.front();
		RevList.pop_front();
		sem_post(&hRevListMutex);
	}
	else
	{
		sem_post(&hRevListMutex);
		return 0;
	}

	memcpy((void*)p, (void*)&msgtemp.Data, size);
	printf("msgtemp.Len: %d\n",(int)(msgtemp.Len));
	return msgtemp.Len;
}
