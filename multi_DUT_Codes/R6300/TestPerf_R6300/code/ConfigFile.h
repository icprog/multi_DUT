#include <list>
#include <semaphore.h>
#include "HashMapPara.h"
using namespace std;

class CConfigFile
{
public:
	CConfigFile(void);
public:
	~CConfigFile(void);

public:
	int GetValidLine(char *pDesBUFF,char *pRtnConBUFF, int RtnSize);
	int JudgeStr(char *pBuf);
	int ReadFileToMem(char *pfile_name);
    int GetLoadConfigFile(char *pfile_name);
	int LegalJudge();
	int FindPaketSEflag(char *PBuf, size_t DataLen);
	int InsertHashMap(char *pDesBUFF, char *pTagBuff, char *pRtnConBUFF, int  RtnConBUFFLen);
	int CopyCaseStr(char *pDst, int DstLen, const char *pSrc, char caseCH);
	int RemoveBeforeChrStr(char *pDst, int DstLen, const char *pSrc, char caseCH);
	int opyCaseAfterStr(char *pDst, int DstLen, const char *pSrc, char caseCH);
	unsigned char HEXConvert (unsigned char ucHEX);
	int StrHEXConvert(char *psrc, int iCovertNum,unsigned int *pRtn);
	int ParserGetPara(char *pDesBUFF, const char *pTagBuff, char *pRtnConBUFF, int  RtnConBUFFLen);
    int GetTestStaInfo(char * pBuf, int bufL);
    int GetParaContent(char *pBuf, int  Len);
    int GetItem();
    int GetSegment();
    int PerformParse(char * pFileName);

public:
	char *pContentBuf;
	int TestItemSequence;
	typedef struct MerPaket
	{
		char *pData;
		int DataLen;

	}MER_PAKET;
      list<MER_PAKET> MPaketList;

	typedef struct STnEDFlag
	{
		int StFlagIndex;
		int EdFlagIndex;
	}STNED_FLAG;

	STNED_FLAG StNeDFlag[500];

	int GetTestStaInfo(char * pBuf, int bufL);
	sem_t sem;
};

