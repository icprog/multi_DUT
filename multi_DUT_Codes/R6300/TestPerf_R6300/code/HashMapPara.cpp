/*
	Contains:	hash map support string class
*/



#include <stdlib.h>
#include <stdio.h>
#include "HashMapPara.h"

CHashMapPara::CHashMapPara(void)
{
	int ret;
    ret=sem_init(&hHashMapMutex,0,1);
}

CHashMapPara::~CHashMapPara(void)
{

}
