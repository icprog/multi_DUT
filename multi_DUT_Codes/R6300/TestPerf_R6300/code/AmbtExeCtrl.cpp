/*
Filename:
    AmbtExeCtrl.cpp

Description:
    Functions with common codes test items used.

 */
 
#include "AmbtExeCtrl.h"
#include "AmCommonIO.h"
extern CHashMapPara SFISDataHashMap;

/*
	run .exe file and read the result.
*/
int RunExeFile(TEST_ITEM *pTI,char *result,const char *cmd)
{

	FILE *fread=NULL;
	char IDTemp[200],IDAdd[200],Line[200],*cmdPoint=NULL;
	struct timeval Start_t,Current_t;
	clock_t duration=0;
	memset(IDAdd,0,sizeof(IDAdd));
	memset(IDTemp,0,sizeof(IDTemp));
	memset(Line,0,sizeof(Line));
	cmdPoint = pTI->Para.GetHashMapStrPara(cmd);
	if(!cmdPoint)
	{
		char cmdStr[20]= "";
		sprintf(cmdStr,"No \"%s\"",cmd);
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",cmdStr);
	    amprintf("Error:%s!\n",cmdStr);
		return 3;
	}
	strncpy(IDTemp,cmdPoint,strlen(cmdPoint));
	strcpy(IDAdd,"./");
	strncat(IDAdd,IDTemp,strlen(IDTemp));
	strncat(IDAdd," 2>&1",strlen(" 2>&1"));
	printf("command=%s\n",IDAdd);
	fread = popen(IDAdd,"r");
	gettimeofday(&Start_t,NULL);
	while(duration<25)
	{
    	if(fgets(Line,200,fread)==NULL)
    	{
    	    gettimeofday(&Current_t,NULL);
    	    usleep(100);
    	    duration=Current_t.tv_sec-Start_t.tv_sec;
    	}
    	else
    	{
    		strncat(result,Line,strlen(Line));
    		break;
    	}
    }
	while(!feof(fread))
	{
		memset(Line,0,sizeof(Line));
		if(fgets(Line,200,fread)==NULL)
		{
			break;
		}
		else
		{
			strncat(result,Line,strlen(Line));
		}


	}
    pclose(fread);
	amprintf("UCP or system output:%s\n",result);

	return 1;

}

/*
	run the command to UI.
*/
int RunCommand(TEST_ITEM *pTI,char *result)
{
	
	FILE *fread=NULL;
	char IDTemp[200],IDAdd[200],Line[200],*cmdPoint=NULL;
	struct timeval Start_t,Current_t;
    clock_t duration=0;
    
	memset(IDAdd,0,sizeof(IDAdd));
	memset(IDTemp,0,sizeof(IDTemp));
	memset(Line,0,sizeof(Line));
	cmdPoint = pTI->Para.GetHashMapStrPara(DUT_CMD);
	if(!cmdPoint)
	{
		char cmdStr[20]= "";
		sprintf(cmdStr,"No \"%s\"",DUT_CMD);
		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",cmdStr);
	    amprintf("Error:%s!\n",cmdStr);
		return 3;
	}
	strncpy(IDTemp,cmdPoint,strlen(cmdPoint));
	strncat(IDAdd,IDTemp,strlen(IDTemp));
	strncat(IDAdd," 2>&1",strlen(" 2>&1"));
	printf("command%s\n",IDAdd);
	
	fread = popen(IDAdd,"r");
	gettimeofday(&Start_t,NULL);
	while(duration<25)
	{
    	if(fgets(Line,200,fread)==NULL)
    	{
    	    gettimeofday(&Current_t,NULL);
    	    usleep(100);
    	    duration=Current_t.tv_sec-Start_t.tv_sec;
    	}
    	else
    	{
    		strncat(result,Line,strlen(Line));
    		break;
    	}
    }
	while(!feof(fread))
	{
		memset(Line,0,sizeof(Line));
		if(fgets(Line,200,fread)==NULL)
		{
			break;
		}
		else
		{
			strncat(result,Line,strlen(Line));
		}


	}
    pclose(fread);
	amprintf("Command or system output:%s\n",result);
	
	return 1;

} 

/*
	check the config file format right.
*/
int EnsureConfigResult(TEST_ITEM *pTI,const char *cmd,const char *spec,int flag)
{       char result[5200],SpecValue[5200],log[1024],*specPoint=NULL;
        memset(result,0,sizeof(result));
        memset(SpecValue,0,sizeof(SpecValue));
        memset(log,0,sizeof(log));
        int value=RunExeFile(pTI,result,cmd);
        if(value==3)
        	return 3;
        if(strncmp(result,"received:",strlen("received:")))
        {
        	if(strstr(result,"\n"))
        	{
            	strncpy(log,result,strstr(result,"\n")-result);
            	pTI->Para.ModifyHashMapItem("ERR_DES_ADD",log);
            }
            else
            {
               pTI->Para.ModifyHashMapItem("ERR_DES_ADD",result);
            } 
	        amprintf("Error message:%s",result);
            if(strstr(result,"connect: No route to host"))
                return 5;
             else if(strstr(result,"connect: Connection refused"))
                return 6;
        	return 2;
        }
        specPoint = pTI->Para.GetHashMapStrPara(spec);
        if(!specPoint)
        {
        	
            char specStr[20]= "";
    		sprintf(specStr,"No \"%s\"",spec);
    		pTI->Para.ModifyHashMapItem("ERR_DES_ADD",specStr);
    	    amprintf("Error:%s!\n",specStr);
        	return 3;
        }
	strncpy(SpecValue,specPoint,strlen(specPoint));
	amprintf("Value in Config=%s\n",SpecValue);
	if(flag == LOG_TO_MYDAS)
	{
	    memset(pTI->Result.Result,0,sizeof(pTI->Result.Result));
	    char result1[5200];
	    memset(result1,0,sizeof(result1));
	    strcpy(result1,result);
	    char *result1End = NULL;
	    result1End = strstr(result1+10,"\n");
	    if(result1End)
        {
            *result1End = '\0';
        }
	    strcpy(pTI->Result.Result,result1+10);
	   
	    memset(pTI->Result.ResultAim,0,sizeof(pTI->Result.ResultAim));
	    strncpy(pTI->Result.ResultAim,SpecValue,strlen(SpecValue));
	}
	
	if(!strncmp(result+10,SpecValue,strlen(SpecValue)))
		return 1;
	else
		return 0;
}
