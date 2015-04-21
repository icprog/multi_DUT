#pragma once

class CAmParser
{
public:
	CAmParser(void);
public:
	~CAmParser(void);

public:
	int ParserGetPara(char *pDesBUFF,const char *pTagBuff, char *pRtnConBUFF, unsigned int RtnConBUFFLen);
	/*this function is copy some character from string to other case one spec character was happen*/
	int CopyCaseStr(char *pDst, int DstLen, const char *pSrc,  char *caseCH);
	void SetStartStopTag(const char *pStart,const char *pStop);
	int ParserGetParaMulti(char *pDesBUFF, char *pTagBuff);//For parser more than one tag


private:
	char StartTag[50];
	char StopTag[50];

};
