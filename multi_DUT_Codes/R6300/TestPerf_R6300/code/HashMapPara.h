
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


using namespace std;

class CHashMapPara
{
public:
	CHashMapPara(void);
public:
	~CHashMapPara(void);

public:   
	sem_t  hHashMapMutex;
	map <char *, char *> *pParaHashMap;
};


#endif
