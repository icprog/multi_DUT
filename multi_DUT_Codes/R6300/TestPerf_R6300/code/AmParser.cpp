#include "string.h"
#include "AmParser.h"
#include <stdio.h>

CAmParser::CAmParser(void)
{
	strcpy(StartTag,"=");
	strcpy(StopTag, ";");
}

CAmParser::~CAmParser(void)
{


}

void CAmParser::SetStartStopTag(const char *pStart,const char *pStop)
{

	if (!pStart || !pStop)
	{
		return;
	}
	strcpy(StartTag, pStart);
	strcpy(StopTag, pStop);

	return;
}

int CAmParser::CopyCaseStr(char *pDst, int DstLen, const char *pSrc, char *caseCH)
{

	const char *pTok=0;

	if ((!pDst)||(!pSrc))
	{
		return 0;
	}

	pTok=strstr(pSrc, caseCH);
	if (!pTok)
	{
		*pDst=0;
		return 0;
	}
	char* pstr=strncpy(pDst,pSrc,(pTok-pSrc));
	if(pstr)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int CAmParser::ParserGetPara(char *pDesBUFF,const char *pTagBuff,char *pRtnConBUFF, unsigned int RtnConBUFFLen)
{
	char TagBUFF[128] = "";
	char AnalyseBUFF[512] = "";
	char ItemID[100]="";
	char *pToken = 0;
	char *pFlagToken = 0;
	char *pConStart = 0;
	char *PConEnd = 0;

	if((0==pDesBUFF)||(0==pTagBuff)||(0==pRtnConBUFF))
	{
		return 0;
	}
	if ((RtnConBUFFLen <= 0) || (RtnConBUFFLen > 512))
	{
		return 0;
	}
	
	strcpy(AnalyseBUFF, pDesBUFF);
	strcpy(TagBUFF, pTagBuff);

	pFlagToken = 0;

	pFlagToken = AnalyseBUFF;
	pFlagToken=strstr(pFlagToken,TagBUFF);
	while(pFlagToken)
	{
		if (!CopyCaseStr(ItemID, sizeof(ItemID),pFlagToken,StartTag))
		{
			printf("ItemID:%s\n",ItemID);
			strcpy(pRtnConBUFF, "");
			return 0;
		}

		if (strlen(ItemID)!=strlen(TagBUFF))
		{
			strcpy(pRtnConBUFF, "");
			return 0;
		}


		if (!strncmp(ItemID, TagBUFF, strlen(TagBUFF)))
		{
			pToken = strstr(pFlagToken, StartTag); 
			if (pToken)
			{
				pConStart = pToken;
				pConStart += 1;  
			}
			else
			{
				return 0;
			}
			pToken = strstr(pToken, StopTag); 
			if (pToken)
			{
				PConEnd = pToken;
				*PConEnd = 0;
			}
			else
			{
				return 0;
			}
			if (pConStart && PConEnd)
			{
				strcpy(pRtnConBUFF, pConStart);
			}	
			return 1;
		}
		else
		{
			strcpy(pRtnConBUFF, "");
			return 0;
		}
	}
	return 0;
}


