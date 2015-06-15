#ifndef AMBT_PARSER_H
#define AMBT_PARSER_H
#include "AmbtTestSysDef.h"

#define FILE_PASER_BUF_L 512

/*parser the parameter from data*/
int ParserGetPara(char *pDesBUFF, const char *pTagBuff, char *pRtnConBUFF, int RtnConBUFFLen);

/*this function is copy some character from string to other case one spec character was happen*/
int CopyCaseStr(char *pDst, int DstLen, const char *pSrc, char caseCH);

#endif

