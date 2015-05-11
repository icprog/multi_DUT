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

 