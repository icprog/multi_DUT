
/*

	Contains:	hash map support string class

	Version:	v1.0.0.1

	Copyright:	(C) 2015 by Ambit Micro, Inc., all rights reserved.

	Change History (most recent first):

	Create by FaHong Zhou 2015/04/16

*/


#ifndef HASH_MAP_PARA_H
#define HASH_MAP_PARA_H



#include <utility>
#include <map>
#include <semaphore.h>
#include <errno.h>

#define STR_LENGTH 1024

using namespace std;

class CHashMapPara
{
public:
	CHashMapPara(void);
public:
	~CHashMapPara(void);

public:
	int CreateHashMapPara();//create and initial hashmap, must call in start
	void DestroyHashMapPara();//release hashmap memory, must call when pragram stop
	int InsertHashMapPara(const char *pfirst,const char *psecond);//insert pair data to hash map
	int FindHashMapPara(char *pfirst, char *pRtnSecond, int RtnSize);//find data in table use first key value
	map <char *, char *> *GetHashMap();//Get hash map point from object
	char *GetHashMapStrPara(const char *pfirst);//find data use first key value and return find string point
	int GetHashMapIntPara(const char *pfirst);//find int data use first key value
	int DeleteHashMapItem(const char *pfirst);
	void DeleteHashMapParaData();
	int ModifyHashMapItem(const char *pfirst,char *psecond);
    void ShowHashMapPara();
    
	sem_t  hHashMapMutex;
	map <char *, char *> *pParaHashMap;
};

#endif
