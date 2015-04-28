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