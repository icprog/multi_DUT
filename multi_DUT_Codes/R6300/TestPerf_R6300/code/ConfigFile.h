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

