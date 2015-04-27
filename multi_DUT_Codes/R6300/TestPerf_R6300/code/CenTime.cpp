#include "CenTime.h"
#include <string.h>

CCenTime::CCenTime(void)
{
}

CCenTime::~CCenTime(void)
{
}
void CCenTime::GenCurrentTime(char *timebuf, int Len)
{

    struct timeval tv;
    struct tm* ptm;
    char time_string[32];
    long milliseconds;
    
  	gettimeofday(&tv,NULL);
	ptm = localtime(&tv.tv_sec);
	strftime(time_string,sizeof(time_string),"%Y-%m-%d %H:%M:%S",ptm);
	milliseconds=tv.tv_usec/1000;
	sprintf(timebuf,"%s.%03d",time_string,(int)milliseconds);

     return;
}
void CCenTime::TimeStartCount()
{
	gettimeofday(&Start_t,NULL);
	return;
}
void CCenTime::GetElapseTime(char *prRtn,int Len)
{
	clock_t Duration=0;
	int Hours=0;
	int Min=0;
	int Seconds=0;
	int MSeconds=0;
	int Temp=0;
	char TimeStrBuf[100];

    gettimeofday(&Current_t,NULL);
	Duration=Current_t.tv_sec-Start_t.tv_sec;
	Hours=Duration/(60*60);
	Temp=Duration%(60*60);
	Min=Temp/(60);	
	Temp=Temp%(60);
	Seconds=Temp;
	MSeconds=(Current_t.tv_usec-Start_t.tv_usec)/1000;
    if(MSeconds < 0)
    {
        if(Seconds < 1)
        {
           if(Min <1 )
            {
                Hours--;
                Min += 60;
            }
           Min--;
           Seconds += 60;
        }
        Seconds--;
        MSeconds += 1000;
    }
	sprintf(TimeStrBuf,"%.2d:%.2d:%.2d.%.3d",Hours,Min,Seconds,MSeconds);
	strcpy(prRtn,TimeStrBuf);
	return;
}
void CCenTime::GetElapseSecond(int *sec)
{
	clock_t Duration=0;
	
	gettimeofday(&Current_t,NULL);
	Duration = Current_t.tv_sec-Start_t.tv_sec;
	*sec = Duration;
	return;
}
void CCenTime::GetDate(char *timebuf, int Len)
{

     struct timeval tv;
    struct tm* ptm;
    char time_string[32];
  	gettimeofday(&tv,NULL);
	ptm = localtime(&tv.tv_sec);
	strftime(time_string,sizeof(time_string),"%Y-%m-%d %H:%M:%S",ptm);
	strcpy(timebuf,time_string);
	return;
}

void CCenTime::DataFormatC(char *timebuf, int Len, char *pIn)
{

    char Otmpbuf[128];
	char Ntmpbuf[128];
	
	if((!timebuf) || (!pIn)) 
	{
		return;
	}

	// 06/17/2008
    // Display operating system-style date and time. 
    strcpy(Otmpbuf,pIn);

	Ntmpbuf[0]=Otmpbuf[6];
	Ntmpbuf[1]=Otmpbuf[7];
	Ntmpbuf[2]=Otmpbuf[8];
	Ntmpbuf[3]=Otmpbuf[9];
	Ntmpbuf[4]=Otmpbuf[0];
	Ntmpbuf[5]=Otmpbuf[1];
	Ntmpbuf[6]=Otmpbuf[3];
	Ntmpbuf[7]=Otmpbuf[4];
	Ntmpbuf[8]=0;
	strcpy(timebuf,Ntmpbuf);

	return;
}
