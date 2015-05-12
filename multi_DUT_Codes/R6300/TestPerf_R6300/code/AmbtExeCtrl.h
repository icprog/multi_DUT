/**
	Control executable file and ensure reslut.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AmbtTestSysDef.h"

/*run .exe file and read the result.*/
int RunExeFile(TEST_ITEM *pTI,char *result,const char *cmd);

/*run the command to UI.*/
int RunCommand(TEST_ITEM *pTI,char *result);

/*check the config file format right.*/
int EnsureConfigResult(TEST_ITEM *pTI,const char *cmd,const char *spec,int flag);

/*check the Muti config file format is right.*/
int EnsureMutiConfigResult(TEST_ITEM *pTI,const char *cmd,const char *spec);

/*check test result.*/
int EnsureResult(TEST_ITEM *pTI,const char *RunResult,const char *cmd);

/*check the SFIF result format right ?*/
int EnsureSFISResult(TEST_ITEM *pTI,const char *cmd,const char *SFISItem,int flag);


 