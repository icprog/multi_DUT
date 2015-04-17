/*
	Contains:	hash map support string class
*/



#include <stdlib.h>
#include <stdio.h>
#include "HashMapPara.h"




#include <stdlib.h>
#include <stdio.h>
#include "HashMapPara.h"
typedef pair<char*,char*> PairData;

CHashMapPara::CHashMapPara(void)
{
	int ret;
    ret=sem_init(&hHashMapMutex,0,1);
}

CHashMapPara::~CHashMapPara(void)
{

}

int CHashMapPara::CreateHashMapPara()
{
    sem_init(&hHashMapMutex,0,1);
	pParaHashMap=0;
	pParaHashMap = new map<char*,char*>;
	if(!pParaHashMap)
	{
		return 0;
	}
	return 1;
}


void CHashMapPara::DestroyHashMapPara()
{
	DeleteHashMapParaData();//clear hash map element and release memory.
	if(pParaHashMap)
	{
		delete pParaHashMap;
		pParaHashMap = NULL;
	}
	return;
}

map <char *, char *> *CHashMapPara::GetHashMap()
{  
	return pParaHashMap;
}

void CHashMapPara::DeleteHashMapParaData()
{
	sem_wait(&hHashMapMutex);
	map<char*,char*>::iterator iter;
	for(iter=pParaHashMap->begin();iter!=pParaHashMap->end();iter++)
	{
		if(iter->first)
		{
			delete iter->first;
		}
		if(iter->second)
		{
			delete iter->second;
			iter->second = NULL;
		}
	}
	sem_post(&hHashMapMutex);

	return;
}
void CHashMapPara::ShowHashMapPara()
{
	printf("One Test Item:\n");
	printf("++++++++++++++++++++++++++++++++++++++++\n");
	sem_wait(&hHashMapMutex);
	map<char*,char*>::iterator iter;
	for(iter=pParaHashMap->begin();iter!=pParaHashMap->end();iter++)
	{
		printf("Map Item:%s\n",iter->first);
		printf("Map Data:%s\n",iter->second);
	}
	sem_post(&hHashMapMutex);
	return;
}
int  CHashMapPara::InsertHashMapPara(const char *pfirst,const char *psecond)
{        
	if(!pParaHashMap)
	{     
	    printf("Null map\n");
		return 0;
	}
	sem_wait(&hHashMapMutex);
	int size_first=strlen(pfirst);
	int size_second=strlen(psecond);
	char *temp_first=new char[size_first+1];
	char *temp_second=new char[size_second+1];
	
	strcpy(temp_first,pfirst);
	strcpy(temp_second,psecond);
	pParaHashMap->insert(PairData(temp_first,temp_second));
	sem_post(&hHashMapMutex);
	return 1;
}

int CHashMapPara::FindHashMapPara(char *pfirst, char *pRtnSecond, int RtnSize)
{
	if (!pfirst)
	{
		return 0;
	}
	sem_wait(&hHashMapMutex);
	map<char *,char *>::iterator it = pParaHashMap->find(pfirst);
    if (it != pParaHashMap->end())
    {
        sem_post(&hHashMapMutex);
        strcpy(pRtnSecond,it->second);
    }
	else
	{
		sem_post(&hHashMapMutex);
		return 0;
	}
	return 1;
}

char *CHashMapPara::GetHashMapStrPara(const char *pfirst)
{
	if (!pfirst)
	{
		return NULL;
	}
	sem_wait(&hHashMapMutex);
	map<char *,char *>::iterator it=pParaHashMap->begin();
	while(it!=pParaHashMap->end())
	{
		if(!strcmp(it->first,pfirst))
		{
			
			break;
		}
		it++;
	}
	if(it!=pParaHashMap->end())
	{
    	sem_post(&hHashMapMutex);
    	return it->second;
	}
	else
	{
    	sem_post(&hHashMapMutex);
    	return NULL;
	}

}
int CHashMapPara::DeleteHashMapItem(const char *pfirst)
{
	if (!pfirst)
	{       
		return 0;
	}


	sem_wait(&hHashMapMutex);
	map<char *,char *>::iterator it = pParaHashMap->begin();
    while (it != pParaHashMap->end())
    {
      	if(!strcmp(it->first,pfirst))
    	{
    		
    		break;
    	}
    	it++;
    } 

   	if(it!=pParaHashMap->end())
	{
		sem_post(&hHashMapMutex);
		
		delete it->first;
		delete it->second;
		it->second = NULL;
		printf("Del Map Return1\n");
		return 1;
	}
	else
	{
		sem_post(&hHashMapMutex);
		printf("Del Map Return0\n");
		return 0;
	}
}
int CHashMapPara::ModifyHashMapItem(const char *pfirst,char *psecond)
{
	if(!pParaHashMap)
	{     
	    printf("Null map\n");
		return 0;
	}
	if (!pfirst)
	{       
		return 0;
	}
	
	sem_wait(&hHashMapMutex);
	
	map<char *,char *>::iterator it = pParaHashMap->begin();
    while (it != pParaHashMap->end())
    {
      	if(!strcmp(it->first,pfirst))
    	{
    		
    		break;
    	}
    	it++;
    } 
	if(it!=pParaHashMap->end())
    {
	    delete (*pParaHashMap)[(char *)pfirst];
    }
    else
    {
    }
	int size_second=strlen(psecond);
	char *temp_second=new char[size_second+1];
    strcpy(temp_second,psecond);
    (*pParaHashMap)[(char *)pfirst]= temp_second;
        
	sem_post(&hHashMapMutex); 
    return 1;
	
	
}
int CHashMapPara::GetHashMapIntPara(const char *pfirst)
{
    if (!pfirst)
	{       
		return 0;
	}


	sem_wait(&hHashMapMutex);
	map<char *,char *>::iterator it = pParaHashMap->begin();
    while (it != pParaHashMap->end())
    {
	  	if(!strcmp(it->first,pfirst))
		{
			
			break;
		}
		it++;
    } 

   	if(it!=pParaHashMap->end())
	{
		sem_post(&hHashMapMutex);
		return atoi(it->second);
	}
	else
	{
		sem_post(&hHashMapMutex);
		return 0;
	}
	
}
