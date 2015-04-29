#include "ConfigFile.h"

#include "AmbitTestSysDef.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_PASER_BUF_L 512
#define PACKET_START '{'
#define PACKET_END '}'

extern TEST_INPUT_INFO gTI;//test input information
list<TEST_ITEM> TItemList;


CConfigFile::CConfigFile(void)
{
	memset(StNeDFlag, -1, sizeof(STNED_FLAG)*500);
	TestItemSequence=1;
}

CConfigFile::~CConfigFile(void)
{
}

int CConfigFile::JudgeStr(char *pBuf)
{
	if (!pBuf)
	{
		return 0;
	}

	if (strchr(pBuf,'\"'))
	{
		if (strchr(pBuf+1,'\"'))
		{
			return 1;
		}
	}
	return 0;
}

int CConfigFile::GetValidLine(char *pDesBUFF,char *pRtnConBUFF, int RtnSize)
{
	char AnalyseBUFF[512]="";

	char *pTok=NULL;
	if ((!pDesBUFF)||(!pRtnConBUFF))
	{
		return 0;
	}
	strcpy(AnalyseBUFF,pDesBUFF);
	pTok = strstr(AnalyseBUFF,"//");
	if (pTok)
	{
		*pTok=0;
	}

	strcpy(pRtnConBUFF,AnalyseBUFF);
	return 1;
}

int CConfigFile::ReadFileToMem(char *pfile_name)
{
	//	char file_name[256];
	char temp_buf[FILE_PASER_BUF_L];
	char FileLineBuf[FILE_PASER_BUF_L];
	char buf[1200];


	char *pcRtnFGet;
	FILE *fpStream = NULL;
	int sNum = 0;
	size_t TotalCnt=0;
	size_t ContentBufL;
	fpStream = fopen(pfile_name,"r");
	if (!fpStream)
	{
		printf("Configuration File1 can't be opened!\n");
		return 0;
	}
	while ( (!feof(fpStream ))&&(sNum!=3))
	{
		pcRtnFGet = fgets(FileLineBuf, FILE_PASER_BUF_L, fpStream);
		memset(temp_buf, 0, sizeof(temp_buf));
		GetValidLine(FileLineBuf,temp_buf, sizeof(temp_buf));
		TotalCnt+=strlen(temp_buf);
	}
	fclose(fpStream);

	fpStream = fopen(pfile_name,"r");
	if (!fpStream)
	{
		printf("Configuration File2 can't be opened!\n");
		return 0;
	}

	ContentBufL=TotalCnt*sizeof(char)+100;
	pContentBuf=(char *)malloc(ContentBufL);
	if (!pContentBuf)
	{
		return 0;
	}
	*pContentBuf=0;
	while ( (!feof(fpStream ))&&(sNum!=3))
	{
		pcRtnFGet = fgets(FileLineBuf, FILE_PASER_BUF_L, fpStream);
		memset(temp_buf, 0, sizeof(temp_buf));
		GetValidLine(FileLineBuf, temp_buf, sizeof(temp_buf));
		strcat(pContentBuf,temp_buf);
	}

	fclose(fpStream);
	memset(buf,0,1200);
	strncat(buf,"rm ",strlen("rm "));
	strncat(buf,pfile_name,strlen(pfile_name));
	system(buf);
	return 1;
}

int CConfigFile::GetLoadConfigFile(char *pfile_name)
{
	char buf[1200];
	memset(buf,0,1200);
	char buf1[1200];
	memset(buf1,0,1200);
	strncat(buf,"tftp -g -l ",strlen("tftp -g -l "));
	strncat(buf,pfile_name,strlen(pfile_name));
	strncat(buf," -r downFile.txt 10.0.0.150",strlen(" -r downFile.txt 10.0.0.150"));
	printf("command:%s\n",buf);
	system(buf);
	
	if (!ReadFileToMem(pfile_name))
	{
		return 0;
	}

	char *token=strtok(pContentBuf, ";");

	memset(buf,0,1200);
	strncat(buf,"tftp -g -l ambitconfig.txt -r ",strlen("tftp -g -l ambitconfig.txt -r "));
	strncat(buf,token,strlen(token));
	strncat(buf," 10.0.0.150",strlen(" 10.0.0.150"));
	printf("command:%s\n",buf);
	system(buf);
	

	return 1;
}

int CConfigFile::LegalJudge()
{

	int iPopFlagIndex=0;

	while(!((StNeDFlag[iPopFlagIndex].StFlagIndex ==-2)&&(StNeDFlag[iPopFlagIndex].EdFlagIndex ==-2)))
	{


		if(((StNeDFlag[iPopFlagIndex].StFlagIndex ==-3)&&(StNeDFlag[iPopFlagIndex].EdFlagIndex ==-3)))// we find nothing
		{
			
			return 0;
		}
		if ((StNeDFlag[iPopFlagIndex].StFlagIndex !=-1)&&(StNeDFlag[iPopFlagIndex].EdFlagIndex !=-1))// we find start and end
		{

		}
		else if (StNeDFlag[iPopFlagIndex].StFlagIndex !=-1)// we find start only
		{
			
			return 0;
		}
		else if (StNeDFlag[iPopFlagIndex].EdFlagIndex !=-1)// we find end only
		{
			
			return 0;
		}
		else
		{
			
			return 0;
		}
		iPopFlagIndex++;

	}
	return 1;
}


int CConfigFile::FindPaketSEflag(char *PBuf, size_t DataLen)
{

	int Index=0;
	int FindTarget=0;
	int insertIndex=0;

	for (Index=0;Index<(int)DataLen;Index++)
	{
		if (PACKET_START == *(PBuf+Index))
		{
			StNeDFlag[insertIndex].StFlagIndex=Index;
			FindTarget=1;

			if (!(Index<(int)DataLen))
			{
				break;
			}
		}

		if(PACKET_END == *(PBuf+Index))
		{

			StNeDFlag[insertIndex++].EdFlagIndex=Index;

			FindTarget=2;
		}
	}
	if (1==FindTarget)
	{
		insertIndex++;
	}
	else if (0==FindTarget)
	{
		StNeDFlag[insertIndex].EdFlagIndex=-3;
		StNeDFlag[insertIndex++].StFlagIndex=-3;
	}
	StNeDFlag[insertIndex].EdFlagIndex=StNeDFlag[insertIndex].StFlagIndex=-2;
	return FindTarget;
}


int CConfigFile::InsertHashMap(char *pDesBUFF, char *pTagBuff, char *pRtnConBUFF, int  RtnConBUFFLen)
{

	char TagBUFF[128] = "";
	char AnalyseBUFF[1024] = "";
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
	char *token=strtok(AnalyseBUFF, ";");
	while( token != NULL )
	{
		token = strtok( NULL, ";" );
	}

	return 0;

	strcpy(AnalyseBUFF,pDesBUFF);
	strcpy(TagBUFF,pTagBuff);


	if (!CopyCaseStr(ItemID, sizeof(ItemID),pFlagToken,'='))
	{
		strcpy(pRtnConBUFF, "");
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
		strcpy(pRtnConBUFF, "");
		return 0;
	}
}

/*this function is copy some character from string to other case one spec character was happen*/
int CConfigFile::CopyCaseStr(char *pDst, int DstLen, const char *pSrc, char caseCH)
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
	strncpy(pDst,pSrc, (pTok-pSrc));
	return 1;
}

int CConfigFile::RemoveBeforeChrStr(char *pDst, int DstLen, const char *pSrc, char caseCH)
{

	const char *pTok=0;

	if ((!pDst)||(!pSrc))
	{
		return 0;
	}

	pTok=strrchr(pSrc, caseCH);
	if (!pTok)
	{
		return(!(strcpy(pDst,pSrc)));
	}

	return(!(strcpy(pDst,pTok+1)));

}

int CConfigFile::CopyCaseAfterStr(char *pDst, int DstLen, const char *pSrc, char caseCH)
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

	return(!(strcpy(pDst,pTok+1)));
}

unsigned char CConfigFile::HEXConvert (unsigned char ucHEX)
{
	unsigned char A = 'A', a='a',zero = '0';

	if (ucHEX >= a) return (ucHEX-a+10);
	if (ucHEX >= A) return (ucHEX-A+10);
	if (ucHEX >= zero) return (ucHEX-zero);

	return 0;
}

int CConfigFile::StrHEXConvert(char *psrc, int iCovertNum,unsigned int *pRtn)
{

	int i = 0;
	int j = 0;
	unsigned int  dwResult=0;
	unsigned  char ByteTemp1 = 0;
	unsigned  char ByteTemp2 = 0;
	unsigned  char ByteTemp = 0;
	char GetBuf[100] = "";
	char BufTemp[100] = "";

	char *pTok=NULL;

	if (!psrc)
	{
		return 0;
	}

	strcpy(BufTemp,psrc);

	pTok=strchr(BufTemp, 'x');
	if (pTok)
	{
		strcpy(GetBuf,(pTok+1));
	}
	else
	{
		return 0;
	}

	for (i = 0,j = 0; i < iCovertNum; i+=2, j++)
	{
		ByteTemp1 = HEXConvert (GetBuf[i]);
		ByteTemp2 = HEXConvert (GetBuf[i+1]);
		ByteTemp = ByteTemp1 << 4 | ByteTemp2;
		dwResult|=ByteTemp;
		if (i>=(iCovertNum-2))
		{
			break;
		}
		dwResult <<= 8;
	}
	*pRtn=dwResult;
	return 1;
}

char *CConfigFile::HexToStrConvert(char *PtrRtn, unsigned int  uiHex)//convert a ui to char
{

	int iIndex = 0;
	int iMaskIndex = 0;
	int iMask = 0xFF;

	if (!PtrRtn)
	{
		return 0;
	}

	for (iIndex = 0,  iMaskIndex = 3; iIndex < 4; iIndex++, iMaskIndex--)
	{
		*(PtrRtn + iIndex) = (uiHex & (iMask<<(8 * iMaskIndex)))>>(8 * iMaskIndex);
	}
	*(PtrRtn + iIndex) = 0;
	return PtrRtn;

}


int CConfigFile::ParserGetPara(char *pDesBUFF, const char *pTagBuff, char *pRtnConBUFF, int  RtnConBUFFLen)
{

	char TagBUFF[128] = "";
	char AnalyseBUFF[1024] = "";
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
		strcpy(pRtnConBUFF, "");
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
		strcpy(pRtnConBUFF, "");
		return 0;
	}

}
}