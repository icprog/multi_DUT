#include "SocketConnection.h"
 
#include <pthread.h>
#include <semaphore.h>

int ConnectionIf;
CSocketConnection *psd;
extern int TestEnd;
extern bool gThreadExitFlag;
extern pthread_t TestThreadID;

void MainConnectionThread(void* lpParameter)
{
	DOT_SOC_BUF RevBuf;
	psd=(CSocketConnection *)lpParameter;
	while(1)
	{
		psd->SocketSer.listen();
		if(!(psd->SocketSer.accept(psd->revSocket))) {
			printf("Can't connect!\n");
		}
     //SendIDInfoToUI();
     ConnectionIf=1;
		int byte_offset=0;

		while(1) {

			if (byte_offset<3004)
			{

				int byterev=0;
				char temp[5120]="";
				byterev=psd->recive_from(temp,5120);
				if(byterev < 0)
				{
					if(byterev==-1)
					{
						if(!gThreadExitFlag)
						{
							printf("Connection lose!\n");
							//psd->ensureSymbol=-1;
							psd->revSocket.close();
							gThreadExitFlag=true;
							if(TestThreadID)
							{
								if(TestThreadID)
								    pthread_cancel(TestThreadID);
							}
							break;
						}
					}
					else
					{
							printf("Connection lose!\n");
							//psd->ensureSymbol=-1;
							psd->revSocket.close();
							gThreadExitFlag=true;
							if(TestThreadID)
							{
								if(TestThreadID)
								    pthread_cancel(TestThreadID);
							}
							break;	
					}
				}
				else if (byterev==0) 
				{
					if(!gThreadExitFlag)
					{
					printf("Connection lose!\n");
					psd->revSocket.close();
					gThreadExitFlag=true;
					}
					else
					{
					printf("Test End! Connnection Lose!\n");
					psd->revSocket.close();
					}
					
					if(TestThreadID)
					{
					    if(TestThreadID)
					        pthread_cancel(TestThreadID);
					}
					break;
				}
				else if(byterev<5)
				{
					psd->ensureSymbol=1;
					printf("Ensure message\n");

				} else
				{

					//printf("CURRENT LEN:%d\n",byte_offset);
					memcpy((char*)RevBuf.Data,temp,byterev);
					RevBuf.Len=strlen(temp);
					byte_offset+=byterev;
					psd->InsertRevList(&RevBuf);
					memset((void*)&RevBuf,0,sizeof(RevBuf));
				}
				byte_offset=0;

				//printf("Step 3\n");
			}



		}

	}
	return;

}


/*
	structor function
*/
CSocketConnection::CSocketConnection()
{
	int ret;
	ret=sem_init(&hRevListMutex,0,1);
}

/*
	destructor function
*/
CSocketConnection::~CSocketConnection()
{

}

/*
	define the data recive from where
*/
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

/*
	insert request socket to the respone list
*/
int CSocketConnection::InsertRevList(DOT_SOC_BUF *p)
{
	sem_wait(&hRevListMutex);
	RevList.push_back(*p);
	sem_post(&hRevListMutex);
	return 1;
}

/*
	send data to connection socket
*/
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

/*
	create connection thread 
*/
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

/*
	get the connection request socket list 
*/
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
