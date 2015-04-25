#include "AmbitParser.h"

/*this function is copy some character from string to other case one spec character was happen*/
int CopyCaseStr(char *pDst, int DstLen, const char *pSrc, char caseCH)
{

	const char *pTok=0;

	if ((!pDst)||(!pSrc))
	{
		return 0;
	}

	pTok=strchr(pSrc, caseCH);
	if (!pTok)
	{
		*pDst=0;
		return 0;
	}

	char *pstr=strncpy(pDst,pSrc, (pTok-pSrc));
	if(pstr)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*parser the parameter from data*/
int ParserGetPara(char *pDesBUFF, const char *pTagBuff, char *pRtnConBUFF, int RtnConBUFFLen)
{
	char TagBUFF[128] = "";
	char AnalyseBUFF[512] = "";
	char ItemID[100]="";
	char *pToken = NULL;
	char *pFlagToken = NULL;
	char *pConStart = NULL;
	char *PConEnd = NULL;

	if((NULL==pDesBUFF)||(NULL==pTagBuff)||(NULL==pRtnConBUFF))
	{
		return 0;
	}
	if ((RtnConBUFFLen <= 0) || (RtnConBUFFLen > 512))
	{
		return 0;
	}
	
	
	strcpy(AnalyseBUFF,pDesBUFF);
	strcpy(TagBUFF,pTagBuff);

	pFlagToken = NULL;
	pFlagToken=strstr(AnalyseBUFF,TagBUFF);
	if (!pFlagToken)
	{
        return 0;
	}

	if (!CopyCaseStr(ItemID, sizeof(ItemID),pFlagToken,'='))
	{
		strcpy(pRtnConBUFF,"");
		return 0;
	}

	if (strlen(ItemID)!=strlen(TagBUFF))
	{
		strcpy(pRtnConBUFF,"");
		return 0;
	}


	if (!strncmp(ItemID, TagBUFF, strlen(TagBUFF)))
	{
		pToken = strstr(pFlagToken, "="); 
		if (pToken)
		{
			pConStart = pToken;
			pConStart += 1;  
		}
		else
		{
			return 0;
		}
		pToken = strstr(pToken, ";"); 
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
			strcpy(pRtnConBUFF,pConStart);
		}	
		return 1;
	}
	else
	{
		strcpy(pRtnConBUFF,"");
		return 0;
	}

}

