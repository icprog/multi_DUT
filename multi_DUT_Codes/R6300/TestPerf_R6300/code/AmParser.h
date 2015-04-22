#pragma once

class CAmParser
{
public:
	CAmParser(void);
public:
	~CAmParser(void);

public:

	/*This function is parser parameter character from data*/
	int ParserGetPara(char *pDesBUFF,const char *pTagBuff, char *pRtnConBUFF, unsigned int RtnConBUFFLen);
	
	/*this function is copy some character from string to other case one spec character was happen*/
	int CopyCaseStr(char *pDst, int DstLen, const char *pSrc,  char *caseCH);
	
	/*This function is copy Start tag and Stop Tag*/
	void SetStartStopTag(const char *pStart,const char *pStop);
	
	/*For parser more than one tag*/
	int ParserGetParaMulti(char *pDesBUFF, char *pTagBuff);


private:
	char StartTag[50];
	char StopTag[50];

};
