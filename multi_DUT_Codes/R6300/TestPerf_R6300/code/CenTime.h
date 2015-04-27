#ifndef CCEN_TIME_H
#define CCEN_TIME_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>


class CCenTime
{
public:
	CCenTime(void);
public:
	~CCenTime(void);
public:
	void TimeStartCount();
public:
	void GenCurrentTime(char *timebuf, int Len);
	void GetElapseTime(char *prRtn,int Len);
        void GetDate(char *timebuf, int Len);
	void DataFormatC(char* timebuf,int Len,char *pIn);
	void GetElapseSecond(int *sec);

private:
	struct timeval Start_t,Current_t;
};
#endif


